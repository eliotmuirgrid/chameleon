//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTapp
//
// Author: Eliot Muir
//
//
// Description:
//
// Implementation
//---------------------------------------------------------------------------
#include <TEST/TESTapp.h>
#include <TEST/TESTfilter.h>
#include <TEST/TESTlastFailed.h>
#include <TEST/TESTrun.h>
#include <TEST/TESTlistTests.h>

#include <COR/CORcommandLine.h>

#include <SCK/SCKutils.h> // needed for windows.

#include <COR/CORlog.h>
COR_LOG_MODULE;

void TESTapp::add(const CORstring& Name, TESTtest pFunc){
   COR_METHOD(TESTapp::add);
   if (m_TestCollection.count(Name) > 0){
      CORcout << "Test: " << Name + " already defined.  Please select a unique name." << newline;
      abort();
   }
   m_TestCollection.add(Name, CORnewClosure0(pFunc));
}

void TESTapp::addClosure(const CORstring& Name, CORclosure0* pFunc){
   COR_METHOD(TESTapp::addClosure);
   if (m_TestCollection.count(Name) > 0){
      CORcout << "Test: " << Name + " already defined.  Please select a unique name." << newline;
      abort();
   }
   m_TestCollection.add(Name, pFunc);
}

bool TESTinit(int argc,const char** argv, CORmap<CORstring, CORauto<CORclosure0> >* pTestCollection){
   COR_FUNCTION(TESTinit);
   SCKinitWinsock();
   CORcommandLine LineParser;
   CORstring ParseError;
   CORlogAddCommandLineFlags(LineParser);
   LineParser.addFlagWithArgument("test", "Glob expression to use.");
   LineParser.addFlagWithoutArgument("lastfailed", "Rerun last failed tests from lastfailed.tmp file.");
   LineParser.addFlagWithoutArgument("showtests", "List the tests availale.");
   if (!LineParser.parseArgs(argc, argv, &ParseError)){
      CORcout << ParseError << newline;
      LineParser.showUsage(&CORcout);
      return false;
   }
   COR_LOG_INIT(argc, argv);
   if (LineParser.isFlagPresent("showtests")){
      TESTlistTests(*pTestCollection);
      return false;
   }
   if (LineParser.isFlagPresent("test")){
      TESTfilterTests(LineParser.flagArgument("test"), pTestCollection);
      if (pTestCollection->size() == 0){
         CORcout << "No tests matched specification.  Use --showtests to show the available tests." << newline;
         return false;
      }
   }
   if (LineParser.isFlagPresent("lastfailed")){
      TESTfilterFailedTests(pTestCollection);
   }
   return true;
}

int TESTapp::run(int argc,const char** argv){
   COR_METHOD(TESTapp::run);
   try{
       if (!TESTinit(argc, argv, &m_TestCollection)){
          return EXIT_FAILURE;
       }
       CORcout << "Running with threads " << m_TestCollection.size() << " test" << (m_TestCollection.size() != 1 ? "s." : ".") << newline;
       return TESTrunTestCollection(m_TestCollection);
   }catch(const TESTfailure& Failure){
       CORcout << Failure << newline;
       return EXIT_FAILURE;
   }catch(const CORstring& Error){
       CORcout << Error << newline;
       return EXIT_FAILURE;
   }catch (...){
       CORcout << "Unhandled exception." << newline;
       return EXIT_FAILURE;
   }
}

int TESTapp::runSingleThreaded(int argc,const char** argv){
   COR_METHOD(TESTapp::runSingleThreaded);
   try{
       if (!TESTinit(argc, argv, &m_TestCollection)){
          return EXIT_FAILURE;
       }
       CORcout << "Running on single thread " << m_TestCollection.size() << " test" << (m_TestCollection.size() != 1 ? "s." : ".") << newline;
       return TESTrunSingleThreadedTestCollection(m_TestCollection);
   }catch(const TESTfailure& Failure){
       CORcout << Failure << newline;
       return EXIT_FAILURE;
   }catch(const CORstring& Error){
       CORcout << Error << newline;
       return EXIT_FAILURE;
   }catch (...){
       CORcout << "Unhandled exception." << newline;
       return EXIT_FAILURE;
   }
}
