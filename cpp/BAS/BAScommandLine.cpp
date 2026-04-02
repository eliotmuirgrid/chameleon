//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BAScommandLine
// 
// Implementation
//-------------------------------------------------------

#include <BAS/BAScommandLine.h>

#include <string.h>

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

BAScommandLine::BAScommandLine(){
   BAS_METHOD(BAScommandLine::BAScommandLine);
}

BAScommandLine::~BAScommandLine(){
   BAS_METHOD(BAScommandLine::~BAScommandLine);
}

void BAScommandLine::add(const BASstring& Name, const BASstring& Description, const BASstring& Placeholder){
   BAS_METHOD(BAScommandLine::add);
   m_Options.add(Name, BASoption(Description, Placeholder));
}

bool BAScommandLine::parse(int argc, const char** argv, BASstring* pError){
   BAS_METHOD(BAScommandLine::parse);
   BAS_VAR(argv[0]);
   if (pError){
      pError->clear();
   }
   m_BinaryName = argv[0];

   for(auto i=m_Options.begin(); i != m_Options.end(); ++i){
      i.value().IsPresent = false;
      i.value().Value.clear();
   }

   int i = 1;
   while (i < argc){
      BAS_VAR(argv[i]);
      if (strlen(argv[i]) < 3 || argv[i][0] != '-' || argv[i][1] != '-'){
         if (pError){
            *pError = "Unexpected argument ";
            *pError += argv[i];
         }
         return false;
      }

      BASstring Name(((char*)argv[i]) + 2);
      BAS_VAR(Name);
      if (!m_Options.has(Name)){
         if (pError){
            *pError = "Unknown flag --";
            *pError += Name;
         }
         return false;
      }

      BASoption& Option = m_Options.value(Name);
      Option.IsPresent = true;
      if (!Option.Placeholder.empty()){
         i++;
         if (i >= argc){
            if (pError){
               *pError = "Missing argument for flag --";
               *pError += Name;
            }
            return false;
         }
         Option.Value = argv[i];
      }
      i++;
   }

   return true;
}

bool BAScommandLine::has(const BASstring& Name) const{
   BAS_METHOD(BAScommandLine::has);
   return m_Options.has(Name) && m_Options.value(Name).IsPresent;
}

const BASstring& BAScommandLine::get(const BASstring& Name) const{
   BAS_METHOD(BAScommandLine::get);
   if (!m_Options.has(Name)){
      static BASstring Empty;
      return Empty;
   }
   return m_Options.value(Name).Value;
}

BASstring BAScommandLine::usage() const{
   BAS_METHOD(BAScommandLine::usage);
   BASstring Result;
   Result += "Usage:\n ";
   Result += m_BinaryName;
   for(auto i=m_Options.cbegin(); i != m_Options.cend(); ++i){
      Result += " --";
      Result += i.key();
      if (!i.value().Placeholder.empty()){
         Result += " <";
         Result += i.value().Placeholder;
         Result += ">";
      }
   }
   Result += "\nOptions:\n";
   for(auto i=m_Options.cbegin(); i != m_Options.cend(); ++i){
      Result += "   --";
      Result += i.key();
      if (!i.value().Placeholder.empty()){
         Result += " <";
         Result += i.value().Placeholder;
         Result += ">";
      }
      Result += " ";
      Result += i.value().Description;
      Result += "\n";
   }
   Result += "\n";
   return Result;
}

BASwriter& operator<<(BASwriter& writer, const BAScommandLine& cmd){
   writer << cmd.usage();
   return writer;
}
