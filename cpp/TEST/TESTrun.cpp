//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTrun
//
// Author: Eliot Muir
//
//
// Description:
//
// Implementation
//---------------------------------------------------------------------------
#include <TEST/TESTrun.h>
#include <TEST/TESTlastFailed.h>

#include <COR/CORthreadPool.h>
#include <COR/CORlog.h>
COR_LOG_MODULE;

#include <SCK/SCKloop.h>

static void TESTcancelTimer(SCKloop* pLoop, int* pId){
   COR_FUNCTION(TESTcancelTimer);
   if (*pId != -1){
      pLoop->cancelTimer(*pId);
      *pId = -1;
   }
}

TESTsummary::~TESTsummary(){
   COR_METHOD(TESTsummary::~TESTsummary);
}

void TESTtimedOut(SCKloop* pLoop, TESTsummary* pSummary){
   COR_FUNCTION(TESTtimedOut);
   CORcout << "Timed out waiting for tests to complete." << newline;
   pLoop->shutdown();
   pSummary->Hung = true;
}

void TESTresetTimeout(SCKloop* pLoop, TESTsummary* pSummary){
   COR_FUNCTION(TESTresetTimeout);
   TESTcancelTimer(pLoop, &pSummary->TimeoutTimerId);
   // JULIAN TO UNDO
   // pSummary->TimeoutTimerId = pLoop->addTimer(CORnewClosure0(&TESTtimedOut, pLoop, pSummary), 10000);  // TODO - might need to expose this in the TESTapp interface.
   pSummary->TimeoutTimerId = pLoop->addTimer(CORnewClosure0(&TESTtimedOut, pLoop, pSummary), 500000);  // TODO - might need to expose this in the TESTapp interface.
}

class TESTstatus{
public:
   CORstring Name;
   int Time;
   CORstring Fail;
};

void TESTupdateSummary(TESTsummary* pSummary, const TESTstatus& Status){
   COR_FUNCTION(TESTupdateSummary);
   COR_VAR(pSummary->TestCount);
   CORcout << pSummary->TestCount;
   if (!Status.Fail.is_null()){
      CORcout << " [FAIL   ] ";
      pSummary->m_FailedBuilds[Status.Name] = Status.Fail;
   } else {
      pSummary->m_FailedBuilds[Status.Name] = "succeeded";
      CORcout << " [Success] ";
      pSummary->CountOfFail--;
   }
   CORcout << Status.Name;
   if (Status.Time > 0){
      CORcout << " [" << Status.Time << " milliseconds]";
   }
   CORcout << newline;
   if (!Status.Fail.is_null()){
      CORcout << Status.Fail << newline;
   }
   (pSummary->TestCount)--;
}

void TESTcomplete(SCKloop* pLoop, TESTsummary* pSummary, TESTstatus Status){
   COR_FUNCTION(TESTcomplete);
   TESTupdateSummary(pSummary, Status);
   if (pSummary->TestCount == 0){
      pLoop->shutdown();
   } else {
      COR_TRC("Reset the timeout.");
      TESTresetTimeout(pLoop, pSummary);
   }
}

TESTstatus TESTexecuteTest(const CORstring& Name, const CORclosure0* pFunc){
   COR_FUNCTION(TESTexecuteTest);
   CORtimeStamp Start;
   CORcurrentTimeStamp(&Start);
   TESTstatus Status;
   try{
      pFunc->run();
   } catch (CORerror& Error){
      Status.Fail = Error.description(); 
   } catch(...){
      Status.Fail = "Unhandled exception.";
   }
   CORtimeStamp End;
   CORcurrentTimeStamp(&End);
   Status.Name = Name;
   Status.Time = CORtimeStampDiffInMillisecond(End,Start);
   return Status;
}

void TESTrunTest(SCKloop* pLoop, CORstring Name, TESTsummary* pSummary, const CORclosure0* pFunc){
   COR_FUNCTION(TESTrunTest);
   TESTstatus Status = TESTexecuteTest(Name, pFunc);
   pLoop->post(CORnewClosure0(&TESTcomplete, pLoop, pSummary, Status));
}

int TESTprintSummary(const TESTsummary& Summary){
   COR_FUNCTION(TESTprintSummary);
   int Result = EXIT_SUCCESS;
   if (Summary.CountOfFail == 0){
      CORcout << "COMPLETE SUCCESS" << newline;
   }else{
      CORcout << Summary.CountOfFail << (Summary.CountOfFail==1 ? " test failed" : " tests failed") << newline;
   }

   for (CORmap<CORstring, CORstring>::const_iterator i = Summary.m_FailedBuilds.cbegin(); i != Summary.m_FailedBuilds.cend(); i++){
      if (i->second != "succeeded"){
         CORcout << " " << i->first << newline;
         Result = EXIT_FAILURE;
      }
   }   
   return Result;
}

int TESTrunTestCollection(const CORmap<CORstring, CORauto<CORclosure0> >& Tests){
   COR_FUNCTION(TESTrunTestCollection);
   if (Tests.size() ==0){
      CORcout << "COMPLETE SUCCESS" << newline;
      return EXIT_SUCCESS;
   }
   CORtimeStamp Start;
   CORcurrentTimeStamp(&Start);
   CORthreadPool Pool(1,100);
   Pool.start();
   SCKloop Loop(&Pool);
   TESTsummary Summary(Tests.size());
   for (auto i = Tests.cbegin(); i != Tests.cend(); i++){
      Summary.m_FailedBuilds.add(i->first, "Timed out");
      Pool.scheduleTask(CORnewClosure0(&TESTrunTest, &Loop, i->first, &Summary, i->second.get()));
   }
   TESTresetTimeout(&Loop, &Summary);
   Loop.start();
   TESTcancelTimer(&Loop, &Summary.TimeoutTimerId);

   CORtimeStamp End;
   CORcurrentTimeStamp(&End);
   CORcout << "Time taken: " << CORtimeStampDiffInMillisecond(End, Start) << " milliseconds " << newline;
   CORcout << newline << "Completed tests - " ;
   int Success = TESTprintSummary(Summary);
   TESTsaveFailedTests(Summary);
   if (Summary.Hung){
      abort();
   }
   return Success;
}

int TESTrunSingleThreadedTestCollection(const CORmap<CORstring, CORauto<CORclosure0> >& Tests){
   COR_FUNCTION(TESTrunSingleThreadedTestCollection);
   if (Tests.size() ==0){
      CORcout << "COMPLETE SUCCESS" << newline;
      return EXIT_SUCCESS;
   }
   CORtimeStamp Start;
   CORcurrentTimeStamp(&Start);
   TESTsummary Summary(Tests.size());
   for (auto i = Tests.cbegin(); i != Tests.cend(); i++){
      Summary.m_FailedBuilds.add(i->first, "Timed out");
      TESTstatus Status = TESTexecuteTest(i->first, i->second.get());
      TESTupdateSummary(&Summary, Status);
   }
   CORtimeStamp End;
   CORcurrentTimeStamp(&End);
   CORcout << "Time taken: " << CORtimeStampDiffInMillisecond(End, Start) << " milliseconds " << newline;
   CORcout << newline << "Completed tests - " ;
   int Success = TESTprintSummary(Summary);
   TESTsaveFailedTests(Summary);
   if (Summary.Hung){
      abort();
   }
   return Success;
}
