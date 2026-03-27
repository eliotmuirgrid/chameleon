//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORlog
//
// Description:
//
// Implementation
//
// Author: Andrew Vajoczki
//---------------------------------------------------------------------------
#include <COR/CORlog.h>

#ifdef COR_ENABLE_TRACING

#include <COR/CORcommandLine.h>

#include <COR/CORerror.h>
#include <COR/CORutils.h>
#include <COR/CORmutex.h>
#include <COR/CORlocker.h>
#include <COR/CORthreadLocal.h>
#include <COR/CORarray.h>
#include <COR/CORsink.h>
#include <COR/CORtimeStamp.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>

#ifdef _WIN32
#   include <windows.h>
#   include <process.h>
#else
#   include <unistd.h>
#   include <pthread.h>
#   include <sys/time.h>
#endif

#define COR_TRACE_INTERNAL(LOGGER,MODULE,MESSAGE)  do { CORlogStream logStream_(LOGGER.getLevel(),MODULE); LOGGER.log(logStream_ << MESSAGE); } while(0)

//
// These CORlog mutex accessor functions are needed due to the initialization
// of static global objects before main() that have CORlog statements.
// It cannot be guaranteed that CORlog.cpp's static mutexes will be initialized
// first, so unfortunately we have have this overhead in accessing mutexes.
//
static inline CORmutex& getTraceLogMutex() {
   // mutex leaked by design to avoid crash after exit in static destructors
   static CORmutex* s_TraceLogMutex = new CORmutex;
   return *s_TraceLogMutex;
}
static inline CORmutex& getTraceTimeMutex() {
   // mutex leaked by design to avoid crash after exit in static destructors
   static CORmutex* s_TraceTimeMutex = new CORmutex;
   return *s_TraceTimeMutex;
}

//
// This class was created to avoid a dependency on the FIL library.
//
class CORlogFile : public CORsink {
public:
   CORlogFile() {
      m_FILE = 0;
   }
   ~CORlogFile() {
      close();
   }
   bool open(const char* filename, CORstring* pError, const char* mode = "w") {
      CORPRECONDITION(m_FILE==0);
      CORPRECONDITION(pError != NULL);
      pError->clear();
      m_FileName = filename;
      if ('+' == m_FileName[0]) {
         // if filename has a '+' prefix, open in append mode
         ++filename; // skip the '+'
         mode = "a"; // append mode
      }
      m_FILE = fopen(filename, mode);
      if (NULL == m_FILE) {
         CORostream ErrorStream(*pError);
         ErrorStream << COR_T("Error: can not open log file '") << m_FileName << '\'';
         return false;
      }
      return true;
   }

   void close() {
      if (m_FILE) {
         fclose(m_FILE);
         m_FILE = 0;
      }
   }
   bool isOpen() const {
      return m_FILE != 0;
   }
   // CORsink virtual methods
   virtual CORuint32 write(const void* buffer, CORuint32 bufferSize) {
      CORPRECONDITION(m_FILE);
      int bytesWritten = fwrite(buffer, 1, bufferSize, m_FILE);
      CORPRECONDITION(bytesWritten == bufferSize);
      return bytesWritten;
   }
   virtual void flush() {
      if (m_FILE) {
         fflush(m_FILE);
      }
   }
   bool reopen(CORstring* pError) {
      CORPRECONDITION(pError != NULL);
      pError->clear();
      m_FILE = fopen(m_FileName.c_str(), "a");
      if (NULL == m_FILE) {
         CORostream ErrorStream(*pError);
         ErrorStream << COR_T("Error: can not open log file '") << m_FileName << '\'';
         return false;
      }
      return true;
   }
private:
   CORstring m_FileName;
   FILE* m_FILE;
};

static CORostream*        gStream = &CORcout;

static int                gWantIndenting = 1;  // indenting is on by default
static int                gStreamWasSet;
static int                gStreamWantFlush = 0;

// must leak thread local indent level due to static dtors that may trace
static CORthreadLocalLong gTraceThreadLocalIndent(false);

static time_t             gLastSecondsSinceEpoch = -1; // guarded by getTraceTimeMutex()
static char               gLastTimeBuffer[40];         // guarded by getTraceTimeMutex()

static CORarray<int*>    gLineEnableVector;   // guarded by getTraceLogMutex()
static CORstring          gDbgArg;             // guarded by getTraceLogMutex()
static CORstring          gTrcArg;             // guarded by getTraceLogMutex()
static CORstring          gInfArg;             // guarded by getTraceLogMutex()
static CORstring          gWrnArg;             // guarded by getTraceLogMutex()
static CORstring          gErrArg;             // guarded by getTraceLogMutex()
static CORstring          gFlushArg;           // guarded by getTraceLogMutex()

// global tracing objects
CORlog g_CORlog_DBG('D');
CORlog g_CORlog_TRC('T');
CORlog g_CORlog_INF('I');
CORlog g_CORlog_WRN('W');
CORlog g_CORlog_ERR('E');

inline unsigned long COR_getCurrentThreadID()
{
#ifdef _WIN32
   return (unsigned long)GetCurrentThreadId();
#else
   return (unsigned long)pthread_self();
#endif
}

CORlogStream::CORlogStream(char level, const char* module) : CORostream(m_String) {
   m_String.setCapacity(240);
   char LinePrefix[128];
   CORtimeStamp currentTime;
   CORcurrentTimeStamp(&currentTime);
   time_t now = (time_t)currentTime.tv_sec;
   {
      // Optimization: cache time string since it is the same 99% of the time.
      // Calling localtime and formatting the string is a very expensive operation.
      CORlocker Lock(getTraceTimeMutex());

      if (now != gLastSecondsSinceEpoch) {
         // optimization to not recompute time string if time is the same
         struct tm tm;
#ifdef _WIN32
         tm = *::localtime(&now); // threadsafe on Windows: uses thread local storage
#else
         localtime_r(&now, &tm);
#endif
         ::snprintf(gLastTimeBuffer, 40, "%02d:%02d:%02d.", tm.tm_hour, tm.tm_min, tm.tm_sec);
         gLastSecondsSinceEpoch = now;
      }
      ::memcpy(LinePrefix+2, gLastTimeBuffer, 9);
   }
   LinePrefix[0] = level;
   LinePrefix[1] = ' ';

   const int millisStart = 11; // position immediately after "T HH:MM:SS."
   const int nowMillis = int(currentTime.tv_usec / 1000);

   // 97% of interfaceware's .cpp file names (w/o suffix) are 28 characters and under.
   // The 2 longest file names are:
   //   45 DBDRPCinterfaceOnMessageRequestCompletedEvent
   //   46 com_interfaceware_chameleon_ChameleonException
   // Only 20 cpp file names are not unique up to 28 characters.
   // The average .cpp file name (w/o suffix) is 15 characters.
   //
   int PrefixLength = millisStart + ::snprintf(LinePrefix+millisStart, 128-millisStart,
       "%03d %012lx %-28s ", nowMillis, COR_getCurrentThreadID(), module);

   assert(PrefixLength<sizeof(LinePrefix)); // do not use CORASSERT or CORPRECONDITION

   // output the tracing prefix "L HH:MM:SS.mmm TTTTTTTT ModuleNameNNNNNNNNNNNNNNNNNN "
    this->write(LinePrefix, PrefixLength);
}

#undef B
#define B "| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | "
static char s_indent_string[] = B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B;
#undef B

const long s_indent_levels = sizeof(s_indent_string) / 2;

CORfunctionLogger::CORfunctionLogger(const char* module, const char* fn, int line, bool doTrace) : _performTrace(doTrace) {
   if (_performTrace) {
      _module = module;
      _fn = fn;

      if (gWantIndenting) {
         // get the thread specific indent level
         long indentLevel = gTraceThreadLocalIndent.get();

         // abort on indent level overflow
         assert(indentLevel < s_indent_levels - 2);

         // output the function with appropriate indent level
         const char* indent = s_indent_string + (s_indent_levels - indentLevel) * 2;
         COR_TRACE_INTERNAL(g_CORlog_TRC, module, indent << '>' << fn << COR_T(" L:") << line);

         // increase the indent level
         gTraceThreadLocalIndent.set(++indentLevel);
      } else {
         COR_TRACE_INTERNAL(g_CORlog_TRC, module, '>' << fn << COR_T(" L:") << line);
      }
   }
}

CORfunctionLogger::CORfunctionLogger(const void* Instance, const char* module, const char* fn, int line, bool doTrace) : _performTrace(doTrace) {
   if (_performTrace) {
      _module = module;
      _fn = fn;

      if (gWantIndenting) {
         // get the thread specific indent level
         long indentLevel = gTraceThreadLocalIndent.get();

         // abort on indent level overflow
         assert(indentLevel < s_indent_levels - 2);

         // output the function with appropriate indent level
         const char* indent = s_indent_string + (s_indent_levels - indentLevel) * 2;
         COR_TRACE_INTERNAL(g_CORlog_TRC, module, indent << '>' << fn << COR_T(" this=") << Instance << COR_T(" L:") << line);

         // increase the indent level
         gTraceThreadLocalIndent.set(++indentLevel); } else {
         COR_TRACE_INTERNAL(g_CORlog_TRC, module, '>' << fn << COR_T(" this=") << Instance << COR_T(" L:") << line);
      }
   }
}

const char* CORfunctionLogger::getIndentLevelString() {
   if (gWantIndenting) {
      return s_indent_string + (s_indent_levels - gTraceThreadLocalIndent.get()) * 2;
   }
   return "";
}

CORfunctionLogger::~CORfunctionLogger() {
   if (_performTrace) {
      if (gWantIndenting) {
         // get the thread specific indent level and decrement it
         long indentLevel = gTraceThreadLocalIndent.get() - 1;
         if (indentLevel < 0) {
            indentLevel = 0;
         }
         gTraceThreadLocalIndent.set(indentLevel);

         // output the function with appropriate indent level
         const char* indent = s_indent_string + (s_indent_levels - indentLevel) * 2;
         COR_TRACE_INTERNAL(g_CORlog_TRC, _module, indent << '<' << _fn);
      } else {
         COR_TRACE_INTERNAL(g_CORlog_TRC, _module, '<' << _fn);
      }
   }
}

CORlog::CORlog(char level) {
   m_Level = level;
}

CORlog::~CORlog() {
}

// called before main() when only a single thread running.
// do not make static.
int COR_gWasInitialized = CORlog::init();

int CORlog::init() {
   return 1;
}

#ifdef _WIN32
#  define COR_LOG_GET_PID() _getpid()
#else
#  define COR_LOG_GET_PID() getpid()
#endif

static CORstring CORlogGetCurrentDir() {
   char Buffer[1024];
#ifdef _WIN32
   GetCurrentDirectory(sizeof(Buffer), Buffer);
#else
   getcwd(Buffer, sizeof(Buffer));
#endif
   return Buffer;
}

static const char CORlogInternal[] = "Acme";

static int gAfterMain; // only log if we are after main()

static void CORlogHeader(int argc, const char** argv) {
   COR_TRACE_INTERNAL(g_CORlog_INF, "", "\n  Timestamp    Thread ID    File  ");

   static const char Line[] = "----------------------------------------------------------------------------";
   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, Line);

   // date
   time_t Now = ::time(0);
   CORstring DateString = ::ctime(&Now);
   DateString.stripAll('\n');
   DateString.stripAll('\r');
   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, DateString);

   // PID
   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, COR_T("PID: ") << COR_LOG_GET_PID());

   // USER
   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, COR_T("USER: ") << ::getenv("USER"));

   // current directory
   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, COR_T("directory: ") << CORlogGetCurrentDir());

   // commandline args
   for (int ArgIndex = 0; ArgIndex < argc; ++ArgIndex) {
      COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, COR_T("argv[") <<ArgIndex<< COR_T("]: ") << argv[ArgIndex]);
   }

   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, Line);
}

void CORlogAddCommandLineFlags(CORcommandLine& LineParser) {
   LineParser.addFlagWithArgument("out"  , "<filename>", "CORlog filename");
   LineParser.addFlagWithArgument("d"    , "<modules>", "CORlog DBG");
   LineParser.addFlagWithArgument("trace", "<modules>", "CORlog TRC");
   LineParser.addFlagWithArgument("i"    , "<modules>", "CORlog INF");
   LineParser.addFlagWithArgument("w"    , "<modules>", "CORlog WRN");
   LineParser.addFlagWithArgument("e"    , "<modules>", "CORlog ERR");
   LineParser.addFlagWithArgument("F"    , "true|false", "CORlog flush");
   LineParser.addFlagWithArgument("n"    , "true|false", "CORlog indenting");
}

void CORlog::init(int argc, const char** argv) {
   if (gAfterMain) return;

   // all tracing is initially disabled
   CORstring dbg;
   CORstring trc;
   CORstring inf;
   CORstring wrn;
   CORstring err;

   for (int a = 1; a < argc; a++) {
      CORstring newFlags = argv[a];

      if (newFlags == "--trace") {
         newFlags = "--t";
      }
      if (newFlags == "--out") {
         newFlags = "--f";
      }

      const CORstring s = newFlags;

      CORstring Argument;
      if (a + 1 < argc) {
         Argument = argv[a+1];
      }

      if (s == "--d") {
         dbg += ' ' + Argument;
         trc += ' ' + Argument;
         inf += ' ' + Argument;
         wrn += ' ' + Argument;
         err += ' ' + Argument;
         CORlocker Lock(getTraceLogMutex());
         gDbgArg = Argument;
      }
      if (s == "--t") {
         trc += ' ' + Argument;
         inf += ' ' + Argument;
         wrn += ' ' + Argument;
         err += ' ' + Argument;
         CORlocker Lock(getTraceLogMutex());
         gTrcArg = Argument;
       }
      else if (s == "--i") {
         inf += ' ' + Argument;
         wrn += ' ' + Argument;
         err += ' ' + Argument;
         CORlocker Lock(getTraceLogMutex());
         gInfArg = Argument;
      } else if (s == "--w") {
         wrn += ' ' + Argument;
         err += ' ' + Argument;
         CORlocker Lock(getTraceLogMutex());
         gWrnArg = Argument;
      } else if (s == "--e") {
         err += ' ' + Argument;
         CORlocker Lock(getTraceLogMutex());
         gErrArg = Argument;
      } else if (s == "--F") {
         const char ch = Argument.size() ? Argument[0] : '1';
         switch (ch) {
         case 'f':
         case 'F':
         case 'n':
         case 'N':
         case '0':
            gStreamWantFlush = 0;
            break;
         default:
            gStreamWantFlush = 1;
            break;
         }
         CORlocker Lock(getTraceLogMutex());
         gFlushArg = Argument;
      }
      else if (s == "--n") {
         const char ch = Argument.size() ? Argument[0] : '1';
         switch (ch) {
         case 'f':
         case 'F':
         case 'n':
         case 'N':
         case '0':
            gWantIndenting = 0;
            break;
         default:
            gWantIndenting = 1;
            break;
         }
      }
      else if (s == "--f") {
         if (gStreamWasSet) {
            CORcerr << COR_T("Error: log output file cannot be specified more than once.\n");
            ::exit(1);
         }

         if (Argument == "stdout") {
            gStream = &CORcout;
            gStreamWasSet = 1;
         }
         else if (Argument == "stderr") {
            gStream = &CORcerr;
            gStreamWasSet = 1;
         }
         else if (Argument != "" && Argument.substr(0,1) != "-"){
            CORlogFile* LogFile = new CORlogFile(); // owned by gStream
            CORstring Error;
            if (!LogFile->open(Argument.c_str(), &Error)) {
               CORcerr << Error << newline;
               ::exit(1);
            }
            if (!LogFile->isOpen()) {
               CORcerr << COR_T("Error: cannot open file '") << Argument << COR_T("'\n");
               ::exit(1);
            }
            //XXX TODO: should lock log file to prevent reuse

            // NOTE: *must* leak because may be used after main().
            gStream = new CORostream(LogFile, true);

            gStreamWasSet = 1;
         }
      }
   }

   {
      CORlocker Lock(getTraceLogMutex());

      // Enable errors and warnings automatically if any of --d, --t or --i is set.
      // To avoid this, just set --e ' ' which is a no-op.
      if ((dbg.size() || trc.size() || inf.size()) && (gWrnArg.is_null() && gErrArg.is_null())) {
         wrn = "*";
         err = "*";
      }

      g_CORlog_DBG.setFilter(dbg);
      g_CORlog_TRC.setFilter(trc);
      g_CORlog_INF.setFilter(inf);
      g_CORlog_WRN.setFilter(wrn);
      g_CORlog_ERR.setFilter(err);
      gAfterMain = 1; // must be last line
   }

   // if --f was specified, or if tracing is on at all - output the log header
   if (gStreamWasSet || g_CORlog_ERR.m_Pattern.size()) {
      CORlogHeader(argc, argv);
      gStream->flush();
   }
}

void CORtrace(const CORstring& Expression){
   const char* pGlob = NULL;
   if (!Expression.is_null()) {
      pGlob = Expression.c_str();
   } else {
      pGlob = getenv("CHM_TRACE");
      if (!pGlob) { return; }
   }
   CORcout << "Tracing on CHM_TRACE=" << pGlob << newline;
   CORlocker Lock(getTraceLogMutex());
   g_CORlog_TRC.setFilter(pGlob);
   g_CORlog_INF.setFilter("");
   g_CORlog_DBG.setFilter("");
   g_CORlog_WRN.setFilter("*");
   g_CORlog_ERR.setFilter("*");
   gAfterMain = 1;
}

void CORsetTraceLogFile(const CORstring& FilePath){
   const char* pFileName = NULL;
   CORlogFile* LogFile = new CORlogFile(); // owned by gStream
   CORstring Error;
   if (!LogFile->open(FilePath.c_str(), &Error)) {
      CORcerr << Error << newline;
      ::exit(1);
   }
   if (!LogFile->isOpen()) {
      CORcout << COR_T("Error: cannot open file '") << pFileName << newline;
      ::exit(1);
   }
   //XXX TODO: should lock log file to prevent reuse

   // NOTE: *must* leak because may be used after main().
   CORlocker Lock(getTraceLogMutex());
   gStream = new CORostream(LogFile, true);
   gStreamWasSet = 1;
   gStreamWantFlush = 1; // Default flushing on .
}

void CORlog::getArgs(CORstring& d, CORstring& t, CORstring& i, CORstring& w, CORstring& e, CORstring& F) {
   CORlocker Lock(getTraceLogMutex());
#if 1
   d = gDbgArg;
   t = gTrcArg;
   i = gInfArg;
   w = gWrnArg;
   e = gErrArg;
#else
   d = g_CORlog_DBG.m_Pattern;
   t = g_CORlog_TRC.m_Pattern;
   i = g_CORlog_INF.m_Pattern;
   w = g_CORlog_WRN.m_Pattern;
   e = g_CORlog_ERR.m_Pattern;
#endif
   F = gFlushArg;
}

static void CORlog_Write(const CORstring& Data) {
   CORlocker Lock(getTraceLogMutex());
   gStream->write(Data.c_str(), Data.size());
}

void CORlog::reset(int argc, const char** argv){
   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, "==reset=====================================================================");
   for (int loop = 0; loop < 2; ++loop)
   {
      gStreamWasSet = 0;
      gAfterMain = 0;
      CORsleep(50); // lame attempt to wait for stray tracing on other threads

      {
         CORlocker Lock(getTraceLogMutex());

         g_CORlog_DBG.setFilter("");
         g_CORlog_TRC.setFilter("");
         g_CORlog_INF.setFilter("");
         g_CORlog_WRN.setFilter("");
         g_CORlog_ERR.setFilter("");

         // reset all the per-line tracing information
         CORarray<int*>::iterator Iter = gLineEnableVector.begin();
         for (; Iter != gLineEnableVector.end(); ++Iter) { *(*Iter) = 0; }
      }

      init(argc, argv);
   }
}

void CORlog::reset(const CORstring& d, const CORstring& t, const CORstring& i, const CORstring& w, const CORstring& e, const CORstring& F) {
   //if (gWantIndenting) return; // can't reset tracing if you have indenting active

   // Note: we're not going to allow resetting the --f logfilename argument

   COR_TRACE_INTERNAL(g_CORlog_INF, CORlogInternal, "==reset=====================================================================");

   // This is a race condition, so we loop twice to try to reset
   // all the threads' static tracing int's correctly.
   for (int loop = 0; loop < 2; ++loop) {
      gAfterMain = 0;
      CORsleep(50); // lame attempt to wait for stray tracing on other threads

      const char* argv[20];
      int argc = 0;
      argv[argc++] = "<program>";
      argv[argc++] = "--d";
      argv[argc++] = d.c_str();
      argv[argc++] = "--t";
      argv[argc++] = t.c_str();
      argv[argc++] = "--i";
      argv[argc++] = i.c_str();
      argv[argc++] = "--w";
      argv[argc++] = w.c_str();
      argv[argc++] = "--e";
      argv[argc++] = e.c_str();
      argv[argc++] = "--F";
      argv[argc++] = F.c_str();

      {
         CORlocker Lock(getTraceLogMutex());

         g_CORlog_DBG.setFilter("");
         g_CORlog_TRC.setFilter("");
         g_CORlog_INF.setFilter("");
         g_CORlog_WRN.setFilter("");
         g_CORlog_ERR.setFilter("");

         // reset all the per-line tracing information
         CORarray<int*>::iterator Iter = gLineEnableVector.begin();
         for (; Iter != gLineEnableVector.end(); ++Iter) { *(*Iter) = 0; }
      }

      init(argc, argv);
   }
}

void CORlog::setFilter(const CORstring& Filter) {
   CORlocker Lock(getTraceLogMutex());
   m_Pattern = Filter;
}

//
// Execute the pattern match at most once per line traced.
//
// Returns:
//  0 for pattern match not executed.
//  1 for pattern match executed, and matched.
// -1 for pattern match executed, but failed to match.
//
int CORlog::enabled(const char* module, int* logstate) const {
   CORstring Pattern;
   {
      CORlocker Lock(getTraceLogMutex());
      gLineEnableVector.push_back(logstate);
      Pattern = m_Pattern;
   }   
#ifdef IFW_RELEASE  
   if (CORstring(module).find("DRX") != npos) { // IX-2935 Hide tracing for license library
      *logstate = 0;
      return *logstate;
   }
#endif
   if (Pattern.size())
   {
      int State = CORglobMatch(Pattern.c_str(), module) ? 1 : -1;
      if (gAfterMain)
      {
         *logstate = State;
         return *logstate > 0;
      }
      return State;
   }
   // no pattern is defined - do not log
   if (gAfterMain)
   {
      *logstate = -1;
   }
   return 0;
}

void CORlog::fini() {
   gStream->flush();
   //XXX Should logging be terminated or should the log file object
   //XXX be allowed to leak in the event that global destructors
   //XXX have tracing?
   if (gStream != &CORcout && gStream != &CORcerr)
   {
      CORostream* oldStream = gStream;
      gStream = &CORcout;
      delete oldStream;
   }
}

void CORlog::log(CORostream& Stream) {
   Stream << '\n';
   CORlogStream* LogStream = dynamic_cast<CORlogStream*>(&Stream);
   CORASSERT(LogStream);
   CORlocker Lock(getTraceLogMutex());
   gStream->write(LogStream->buffer(), LogStream->length());
   if (gStreamWantFlush)
   {
      gStream->flush();
   }
}

// Given a filename like ../../foo/MyModule.cpp return "MyModule".
// Note: this call assumes that a a writable char array passed
// as a parameter.  This array will be changed.
const char* CORlog::getBaseModuleName(char* FileName) {
   assert(FileName && FileName[0]);
   char* module = FileName;
   int len = ::strlen(FileName);
   for (int i = len - 1; i >= 0; --i) {
      char ch = FileName[i];
      if (ch == '/' || ch == '\\') {
         module = FileName + i + 1;
         break;
      }
   }
   for (int m = 0; module[m]; m++) {
      if (module[m] == '.') {
         module[m] = 0;
         break;
      }
   }
   return module;
}

void CORlog::reopenFile() {
   CORlogFile* pLogFile = dynamic_cast<CORlogFile*>(gStream->sink());
   if (pLogFile){
      CORstring Error;
      if (!pLogFile->reopen(&Error)) {
         CORcerr << Error << newline;
         ::exit(1);
      }
   }
}

static const int s_Max_COR_DUMP_WIDTH = 120;

static int get_COR_DUMP_WIDTH() {
   const char* COR_DUMP_WIDTH_string = ::getenv("COR_DUMP_WIDTH");
   if (COR_DUMP_WIDTH_string == NULL) {
      return 16;
   }
   const int COR_DUMP_WIDTH = ::atoi(COR_DUMP_WIDTH_string);
   if (COR_DUMP_WIDTH <= 0) {
      return 10;
   }
   if (COR_DUMP_WIDTH > s_Max_COR_DUMP_WIDTH) {
      return s_Max_COR_DUMP_WIDTH;
   }
   return COR_DUMP_WIDTH;
}

static int get_COR_DUMP_MODE() {
   const char* COR_DUMP_MODE_string = ::getenv("COR_DUMP_MODE");
   if (COR_DUMP_MODE_string == NULL) {
      return 0;
   }
   const int COR_DUMP_MODE = ::atoi(COR_DUMP_MODE_string);
   return COR_DUMP_MODE;
}

void CORlog::dump(const char* module, const void* pData, int nbytes) const {
   //const char COR_MODULE[] = "CORlog";
   //COR_FUNCTION(CORlog::dump);
   static const char Hex[] = "0123456789abcdef?";
   static int s_COR_DUMP_WIDTH = ::get_COR_DUMP_WIDTH();
   static int s_COR_DUMP_MODE  = ::get_COR_DUMP_MODE();
   if (nbytes <= 0 || pData == NULL) { return; }
   const unsigned char* data = (const unsigned char*)pData;
   char HexBuf[3 * s_Max_COR_DUMP_WIDTH + 16];
   memset(HexBuf, ' ', 3*(s_COR_DUMP_WIDTH+1));
   char CharBuf[s_Max_COR_DUMP_WIDTH + 16];
   CharBuf[0] = 0;
   int c = 0;
   for (int i = 0; i < nbytes; ++i) {
      CORASSERT(c < s_COR_DUMP_WIDTH);
      const unsigned char ch = data[i];
      int HexBufPos = c * 3;
      const int Printable = isprint(ch);
      if (Printable && s_COR_DUMP_MODE) {
         HexBuf[HexBufPos+1] = (char)ch;
      } else {
         HexBuf[HexBufPos+0] = Hex[(ch & 0xf0) >> 4];
         HexBuf[HexBufPos+1] = Hex[(ch & 0x0f)];
         CharBuf[c] = Printable ? (char)ch : '.';
      }
      if (++c >= s_COR_DUMP_WIDTH || i+1 >= nbytes) {
         CharBuf[c] = 0;
         HexBuf[3*s_COR_DUMP_WIDTH+1] = 0; // subscript is as intended
         char RowPrefix[16];
         snprintf(RowPrefix, 16, "%6d: ", i/s_COR_DUMP_WIDTH*s_COR_DUMP_WIDTH);
         COR_TRACE_INTERNAL((const_cast<CORlog&>(*this)), module,
            CORfunctionLogger::getIndentLevelString() << RowPrefix << HexBuf
            << (s_COR_DUMP_MODE ? "" : CharBuf));
         c = 0;
         memset(HexBuf, ' ', 3*s_COR_DUMP_WIDTH);
      }
   }
}

#endif // COR_ENABLE_TRACING
