#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORlog
//
// Author: Andrew Vajoczki
//
// Description:
//
// CORlog class - heart of our tracing system.  Worth have a read through this.
//
//  Commandline parameters for controlling conditional logging:
//
//    --f log_filename            # +log_filename to append
//    --d debug_modules_pattern
//    --t trace_modules_pattern
//    --i info_modules_pattern
//    --w warning_modules_pattern
//    --e error_modules_pattern
//    --F true|false              # flush each trace line
//    --n true|false              # indenting; on by default.
//
//  Example:
//
//    program --t "ABCabc FOO* -FOObar*" --w "ABC* XYZ*" --f out.log
//
//  This will enable TRC INF WRN ERR conditional logging for module
//  'ABCabc' as well as modules beginning with 'FOO' - but not
//  modules beginning with 'FOObar'.
//  WRN and ERR conditional logging will be enabled for modules beginning
//  with 'ABC' or 'XYZ'. No DBG level logging will be enabled, as --d
//  was not specified.
//
//  A '-' before a pattern indicates exclusion. Pattern order is
//  significant - patterns are evaluated from left to right.
//
//  Tracing will be logged to the file "out.log".
//  If --f is not specified conditional logging will go to stdout.
//
//    --d applies to the levels: DBG TRC INF WRN ERR
//    --t applies to the levels:     TRC INF WRN ERR
//    --i applies to the levels:         INF WRN ERR
//    --w applies to the levels:             WRN ERR
//    --e applies to the levels:                 ERR
//
//  If no arguments are supplied conditional logging defaults to no logging.
//
//  Note: when used from the shell, the * character will expand to a random
//  filename on UNIX, so always remember to put quotes around each argument.
//
//---------------------------------------------------------------------------

#include <COR/CORostream.h>
#include <COR/CORstring.h>

#define COR_ENABLE_TRACING

#ifdef COR_ENABLE_TRACING // logging is on by default.

class CORlogStream : public CORostream
{
   CORstring m_String;
public:
   CORlogStream(char level, const char* module);
   ~CORlogStream() { }
   int length() const { return static_cast<int>(m_String.size()); }
   const char* buffer() const { return m_String.c_str(); }
private:
   CORlogStream(const CORlogStream&); // disallow
   CORlogStream& operator=(const CORlogStream&); // disallow
};

// --trace "* -COR" --level 4 --file "trace.log" --flush
// Defaults
//  level = 3
//  Standard output
//  No flushing

// API to use if you don't want or cannot set tracing via command line
// loads the tracing glob expression from env var CHM_TRACE by default
void CORtrace(const CORstring& Expression = "");
// loads the tracing file path from env var CHM_TRACE_FILE by default
void CORsetTraceLogFile(const CORstring& FilePath = "");
//void CORdebug(const char** Glob);

class CORcommandLine;

#ifdef COR_ENABLE_TRACING
void CORlogAddCommandLineFlags(CORcommandLine& LineParser);
#else
inline void CORlogAddCommandLineFlags(CORcommandLine&) {}
#endif

class CORlog{
public:
   static void init(int argc, const char** argv);
   static int init();
   static void fini();
   static void getArgs(CORstring& d, CORstring& t, CORstring& i, CORstring& w, CORstring& e, CORstring& F);
   static void reset(int argc, const char** argv);
   static void reset(const CORstring& d, const CORstring& t, const CORstring& i, const CORstring& w, const CORstring& e, const CORstring& F);
   static const char* getBaseModuleName(char* filename);
   static void reopenFile();
   CORlog(char level);
   virtual ~CORlog();
   void log(class CORostream& logstream);
   char getLevel() const { return m_Level; }
   void setFilter(const CORstring& ModulesPattern);
   int enabled(const char* module, int* logState) const;
   void dump(const char* module, const void* data, int nbytes) const;
private:
   CORlog();
   CORlog(const CORlog&);
   CORlog& operator=(const CORlog&);
private:
   char m_Level; // One of: T, I, W, E.
   // A whitespace-separated string of globs. Example: "ABC* XYZ* FOO*"
   CORstring m_Pattern; // guarded by gTraceLogMutex
};

class CORfunctionLogger{
public:
   CORfunctionLogger(const char* module, const char* fn, int line, bool doTrace);
   CORfunctionLogger(const void* Instance, const char* module, const char* fn, int line, bool doTrace);
   ~CORfunctionLogger();
   static const char* getIndentLevelString();
private:
   int _performTrace;
   const char* _module; // not owned by this instance - assumed to be static
   const char* _fn;     // not owned by this instance - assumed to be static
};

extern CORlog g_CORlog_DBG;
extern CORlog g_CORlog_TRC;
extern CORlog g_CORlog_INF;
extern CORlog g_CORlog_WRN;
extern CORlog g_CORlog_ERR;

// This must be put at the top of each .cpp to be logged (*).
// *NEVER* put this in a header file.
#define COR_LOG_MODULE \
   static char CORlogModule[] = __FILE__; \
   static const char* COR_MODULE = CORlog::getBaseModuleName(CORlogModule)

// (*) An alternative to COR_LOG_MODULE;
// Use either COR_LOG_MODULE *or* COR_LOG_MODULE_CUSTOM - not both.
// *NEVER* put this in a header file.
#define COR_LOG_MODULE_CUSTOM(MODULE_NAME) \
   static char CORlogModule[] = MODULE_NAME; \
   static const char* COR_MODULE = CORlog::getBaseModuleName(CORlogModule)

// The following macros are so cryptic because they have to evaluate
// the glob expression controlling each specific log line just *once*.
// Otherwise the logging would be over 100 times slower due to glob overhead.
// The macros also have to contend with performing logging only after
// the runtime conditional logging system is initialized in main(),
// and not log lines in static initialization code before main().

#define COR_TRACE_BASE(LOGGER,MODULE,MESSAGE) \
   do { \
      static int loGsTaTE_; \
      if (loGsTaTE_ > 0 || (!loGsTaTE_ && LOGGER.enabled(MODULE,&loGsTaTE_))) { \
         CORlogStream logStream_(LOGGER.getLevel(),MODULE); \
         LOGGER.log(logStream_ << CORfunctionLogger::getIndentLevelString() << MESSAGE); \
      } \
   } while (0)

#define COR_ENT(COR_BLOCK_ARG) \
   static int ColEntLogState;\
   CORfunctionLogger ColEntLoggeR(COR_MODULE,COR_BLOCK_ARG,__LINE__,\
      (ColEntLogState>0 || (!ColEntLogState && g_CORlog_TRC.enabled(COR_MODULE, &ColEntLogState))))

#define COR_FUNCTION(COR_FN_ARG) \
   static int ColFnLogState;\
   CORfunctionLogger ColEntFnLoggeR(COR_MODULE,#COR_FN_ARG,__LINE__,\
      (ColFnLogState>0 || (!ColFnLogState && g_CORlog_TRC.enabled(COR_MODULE, &ColFnLogState))))

#define COR_METHOD(COR_FN_ARG) \
   static int ColMethodLogState;\
   CORfunctionLogger ColMethodLoggeR((const void*)(this),COR_MODULE,#COR_FN_ARG,__LINE__,\
      (ColMethodLogState>0 || (!ColMethodLogState && g_CORlog_TRC.enabled(COR_MODULE, &ColMethodLogState))))

// should be first line in main(), or at least before any conditional logging macros.
#define COR_LOG_INIT(ARGC,ARGV) CORlog::init(ARGC,ARGV)
#define COR_LOG_RESET(ARGC, ARGV) CORlog::reset(ARGC, ARGV)
#define COR_LOG_FINI CORlog::fini()

#define COR_DBG(MESSAGE) COR_TRACE_BASE(g_CORlog_DBG,COR_MODULE,MESSAGE)
#define COR_TRC(MESSAGE) COR_TRACE_BASE(g_CORlog_TRC,COR_MODULE,MESSAGE)
#define COR_INF(MESSAGE) COR_TRACE_BASE(g_CORlog_INF,COR_MODULE,MESSAGE)
#define COR_WRN(MESSAGE) COR_TRACE_BASE(g_CORlog_WRN,COR_MODULE,MESSAGE)
#define COR_ERR(MESSAGE) COR_TRACE_BASE(g_CORlog_ERR,COR_MODULE,MESSAGE)

#define COR_VAR(V) COR_TRACE_BASE(g_CORlog_TRC,COR_MODULE,COR_T(#V" = ")<<V)
#define COR_VAR2(V1,V2) COR_TRACE_BASE(g_CORlog_TRC,COR_MODULE,COR_T(#V1" = ")<< V1<<COR_T(", "#V2" = ")<<V2)
#define COR_VAR3(V1,V2,V3) COR_TRACE_BASE(g_CORlog_TRC,COR_MODULE,COR_T(#V1" = ")<< V1<<COR_T(", "#V2" = ")<<V2<<COR_T(", "#V3" = ")<<V3)
#define COR_VAR4(V1,V2,V3,V4) COR_TRACE_BASE(g_CORlog_TRC,COR_MODULE,COR_T(#V1" = ")<< V1<<COR_T(", "#V2" = ")<<V2<<COR_T(", "#V3" = ")<<V3<<COR_T(", "#V4" = ")<<V4)

#define COR_DUMP_BASE(LOGGER,MODULE,MESSAGE,DATA,NBYTES) \
   do { \
      static int loGsTaTE_; \
      if (loGsTaTE_ > 0 || (!loGsTaTE_ && LOGGER.enabled(MODULE,&loGsTaTE_))) { \
         CORlogStream logStream_(LOGGER.getLevel(),MODULE); \
         LOGGER.log(logStream_ << CORfunctionLogger::getIndentLevelString() << MESSAGE << ": " << (NBYTES) << " bytes @ " << (void*)(DATA)); \
         LOGGER.dump(MODULE,DATA,NBYTES); \
      } \
   } while (0)

#define COR_DUMP(    MESSAGE,DATA,NBYTES) COR_DUMP_BASE(g_CORlog_DBG,COR_MODULE,MESSAGE,DATA,NBYTES)
#define COR_DBG_DUMP(MESSAGE,DATA,NBYTES) COR_DUMP_BASE(g_CORlog_DBG,COR_MODULE,MESSAGE,DATA,NBYTES)
#define COR_TRC_DUMP(MESSAGE,DATA,NBYTES) COR_DUMP_BASE(g_CORlog_TRC,COR_MODULE,MESSAGE,DATA,NBYTES)
#define COR_INF_DUMP(MESSAGE,DATA,NBYTES) COR_DUMP_BASE(g_CORlog_INF,COR_MODULE,MESSAGE,DATA,NBYTES)
#define COR_WRN_DUMP(MESSAGE,DATA,NBYTES) COR_DUMP_BASE(g_CORlog_WRN,COR_MODULE,MESSAGE,DATA,NBYTES)
#define COR_ERR_DUMP(MESSAGE,DATA,NBYTES) COR_DUMP_BASE(g_CORlog_ERR,COR_MODULE,MESSAGE,DATA,NBYTES)

// arguments are CORstring&
#define COR_LOG_GET_ARGS(d,t,i,w,e,F) CORlog::getArgs(d,t,i,w,e,F)

// arguments are const CORstring&
#define COR_LOG_RESET_ARGS(d,t,i,w,e,F) CORlog::reset(d,t,i,w,e,F)

#else // !COR_ENABLE_TRACING

#define COR_LOG_MODULE
#define COR_LOG_MODULE_CUSTOM(MODULE_NAME)
#define COR_DBG(MESSAGE)
#define COR_TRC(MESSAGE)
#define COR_INF(MESSAGE)
#define COR_WRN(MESSAGE)
#define COR_ERR(MESSAGE)
#define COR_VAR(V)
#define COR_VAR2(V1,V2)
#define COR_VAR3(V1,V2,V3)
#define COR_VAR4(V1,V2,V3,V4)
#define COR_ENT(BLOCKNAME)
#define COR_FUNCTION(FUNCTION)
#define COR_METHOD(FUNCTION)
#define COR_LOG_INIT(ARGC,ARGV)
#define COR_LOG_RESET(ARGC,ARGV)
#define COR_LOG_FINI
#define COR_LOG_GET_ARGS(d,t,i,w,e,F)
#define COR_LOG_RESET_ARGS(d,t,i,w,e,F)
#define COR_DUMP(    MESSAGE,DATA,NBYTES) do{}while(0)
#define COR_DBG_DUMP(MESSAGE,DATA,NBYTES) do{}while(0)
#define COR_TRC_DUMP(MESSAGE,DATA,NBYTES) do{}while(0)
#define COR_INF_DUMP(MESSAGE,DATA,NBYTES) do{}while(0)
#define COR_WRN_DUMP(MESSAGE,DATA,NBYTES) do{}while(0)
#define COR_ERR_DUMP(MESSAGE,DATA,NBYTES) do{}while(0)

#endif // COR_ENABLE_TRACING

