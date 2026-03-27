#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORostream
//
// Description:
//
// CORostream translates C and user defined types into text.  It's modeled
// on the standard iostream library.  Give it a read over - Eliot.
//
// Each CORostream object has a CORsink object which is used to
// write the actual formatted text.  Each CORstream object may or
// may not 'own' the CORsink object that it writes to.
//
// There are a number of standard global objects CORcout, CORcerr,
// CORclog which are commented on further down this file.
//
// To format numbers in hexidecimal we can do the following:
//
// CORcout << hex << Number << " (in hex) " << decimal << Number << 
//        " (in decimal) " << newline << flush;
//
// Note the use of the newline and flush operators.  These will
// add a newline and flush the sink respectively.  Since different
// operating systems have different conventions for newlines there is
// a setNewLine method which allows one to specify the string to insert
// for a newline.
//
// Sometimes I have found it necessary to write:
//
// CORcout << ::flush;  
//
// The problem here is when the above statement is in the context of
// a class which actually implements a flush method - basically anything
// which implements CORsink has this problem.
//
// CORostream can be useful way to convert numbers into strings i.e.
//
// CORuint32 MyNumber = 1221;
// CORstring MyString;
// CORostream Stream(MyString);
//
// Stream << MyNumber;
//
// Author: Eliot Muir
//---------------------------------------------------------------------------

#include <COR/CORstring.h>

class CORostreamPrivate;
class CORsink;

class CORostream{
public:
   // This constructor takes ownership of the sink object.
   CORostream(CORsink* Sink, bool Owner);

   // This constructor does not take ownership of the sink object.
   CORostream(CORsink& Sink);

   // Not too proud of these constructors but they made it easier to stop
   // CORstring have a virtual interface implementing CORsink (Eliot).
   CORostream(CORstring& String); // Makes a CORsinkString which is owned by
                                  // CORostream but the sink does not own String.
   CORostream(CORstring* pString, bool Owner);

// IX-2358 - this is *okay* since adding an extra constructor doesn't alter the size of the class
// Talk to Eliot if you have questions.
#ifdef COR_ENABLE_TRACING
   CORostream(CORsink* Sink, bool Owner, bool Delete_pMember);
#endif

   virtual ~CORostream();

   void flush();
   void newline();

   void setNewLine(const char* NewLine);
   const char* getNewLine() const;

   // The indent content refers to what will be used to make an indented
   // entry.  By default this is set to "   " but one might for certain applications
   // set this to "\t" for a more space efficient indenting mechanism.
   // Most of the time it will be more elegant to use the overloaded operators
   // to invoke these indentation methods i.e.
   // Stream << set_indent("\t")
   //        << add_indent
   //        << "Blah"
   //        << remove_indent;
   // When one wants to remove all indentation one can do:
   // Stream << clear_indent;
   void setIndentContent(const CORstring& Indent);
   const CORstring& indentContent() const;

   void indent();
   void unindent();
   void resetIndent();
   void setCountOfIndent(CORuint32 NewValue);
   CORuint32 countOfIndent() const;

   // Write binary data of a fixed length - no strlen() operation performed.
   // Embedded nulls allowed.
   CORostream& write(const void* Data, int Length);

   CORostream& operator<<(CORostream&(*)(CORostream&)); 
   CORostream& operator<<(CORostream&(*)(CORostream&, int n)); 
   CORostream& operator<<(char Character);
   CORostream& operator<<(unsigned char Character);
   CORostream& operator<<(const char* pString);
   CORostream& operator<<(const CORstring& String);
   CORostream& operator<<(CORfloat64 Number);
   CORostream& operator<<(CORfloat32 Number);
   CORostream& operator<<(CORint16 Number);
   CORostream& operator<<(CORuint16 Number);
   CORostream& operator<<(CORint32 Number);
   CORostream& operator<<(CORuint32 Number);
   CORostream& operator<<(CORuint64 Number);   
   CORostream& operator<<(CORint64 Number);   
   CORostream& operator<<(bool Boolean);
   CORostream& operator<<(const void* Pointer);
   CORostream& operator<<(unsigned long Number) { return operator<<((CORuint32)Number); }   
   CORostream& operator<<(long Number) { return operator<<((CORint32)Number); }   

   // returns true if this CORostream owns its sink object.
   bool isSinkOwner() const;
   CORsink* sink();
   
   CORsink* setSink(CORsink* pSink, bool IsOwner);
   CORsink& setSink(CORsink& Sink) { return *setSink(&Sink, false); }

   enum ENumberBase { Decimal = 10, Hexadecimal = 16 };
   ENumberBase numberBase() const;

private:
   CORostreamPrivate* pMember;

   void setNumberBase( ENumberBase Base );

   friend CORostream& hex(CORostream& _outs);
   friend CORostream& decimal(CORostream& _outs);

   CORostream(const CORostream& Orig);
   CORostream& operator=(const CORostream& Orig);
};

// CORcerr, CORcout and CORclog are equivalent to the
// the standard iostream library's cerr, cout, clog 
// objects.  They are global CORostream objects that go
// to standard error, standard out and in the case of
// CORclog usually standard out.  

extern CORostream CORcerr;
extern CORostream CORcout;
extern CORostream CORclog;

CORostream& flush(CORostream& _outs);
CORostream& newline(CORostream& _outs);

CORostream& indent(CORostream& OutStream);
CORostream& unindent(CORostream& OutStream);
CORostream& reset_indent(CORostream& OutStream);

CORostream& hex(CORostream& _outs);
CORostream& decimal(CORostream& _outs);

class CORostreamManip {
public:
   virtual ~CORostreamManip();
   virtual void printOn(CORostream& Stream) const = 0;
};

// This complicated looking stuff is for implementation CORostream manipulators
// with arguments.
template<class TArgument>
class CORostreamManip1 : public CORostreamManip {
public:
   typedef void (*TCORostreamFunction)(CORostream&, const TArgument&);
   CORostreamManip1(TCORostreamFunction ipFunction, const TArgument& iArgument)
   : pFunction(ipFunction),
     Argument(iArgument)
   {
   }
   virtual void printOn(CORostream& Stream) const
   {
      (*pFunction)(Stream, Argument);
   }
   TCORostreamFunction pFunction;
   TArgument Argument;
};

template<class TArg1, class TArg2>
class CORostreamManip2 : public CORostreamManip {
public:
   typedef void (*TCORostreamFunction)(CORostream&, TArg1, TArg2);
   CORostreamManip2(TCORostreamFunction pFunction, TArg1& Arg1, TArg2& Arg2)
   : m_pFunction(pFunction),
     m_Arg1(Arg1),
     m_Arg2(Arg2)
   {
   }
   virtual void printOn(CORostream& Stream) const
   {
      (*m_pFunction)(Stream, m_Arg1, m_Arg2);
   }
   TCORostreamFunction m_pFunction;
   TArg1 m_Arg1;
   TArg2 m_Arg2;
};


template<class TArg1, class TArg2, class TArg3>
class CORostreamManip3 : public CORostreamManip {
public:
   typedef void (*TCORostreamFunction)(CORostream&, TArg1, TArg2, TArg3);
   CORostreamManip3(TCORostreamFunction pFunction, TArg1& Arg1, TArg2& Arg2, TArg3& Arg3)
   : m_pFunction(pFunction),
     m_Arg1(Arg1),
     m_Arg2(Arg2),
     m_Arg3(Arg3)
   {
   }
   virtual void printOn(CORostream& Stream) const
   {
      (*m_pFunction)(Stream, m_Arg1, m_Arg2, m_Arg3);
   }
   TCORostreamFunction m_pFunction;
   TArg1 m_Arg1;
   TArg2 m_Arg2;
   TArg3 m_Arg3;
};


inline CORostream& operator<<(CORostream& Stream, CORostreamManip* pManipulator) {
   pManipulator->printOn(Stream);
   delete pManipulator;
   return Stream;
}

CORostreamManip* set_indent(const CORstring& TagName);

inline CORostream& operator<<(CORostream& Stream, const CORtextLiteral& Literal) {
   return Stream.write(Literal.m_String, Literal.m_Length);
}

class CORostreamString : public CORostream
{
public:
   CORostreamString();
   virtual ~CORostreamString();

   // The reference returned by str() is only valid until any subsequent
   // non-const method invocaton on the instance of CORostreamString.
   const CORstring& str() const;

   // The pointer returned by c_str() is only valid until any subsequent
   // non-const method invocaton on the instance of CORostreamString.
   const char* c_str() const;

   int size() const { return m_String.size(); }

   void clear() { m_String.clear(); }
private:
   CORstring m_String;
   CORostreamString(const CORostreamString&);            // disallow
   CORostreamString& operator=(const CORostreamString&); // disallow
};

