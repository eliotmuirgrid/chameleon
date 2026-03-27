// ---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORvarJson
//
// Description:
//
// Implementation
//
// Author: Eliot Muir 
// ---------------------------------------------------------------------------

#include <COR/CORvar.h>
#include <COR/CORstring.h>

#include <stdio.h>
#include <ctype.h>

#include <COR/CORlog.h>
COR_LOG_MODULE;

class CORjsonParseState{
public:
   CORstring ErrorMessage;
};

// Forward declarations of parsing functions
static bool CORparseObject (const char*& current, CORvar& value, CORjsonParseState* pState);
static bool CORparseArray  (const char*& current, CORvar& value, CORjsonParseState* pState);
static bool CORparseString (const char*& current, CORvar& value, CORjsonParseState* pState);
static bool CORparseNumber (const char*& current, CORvar& value, CORjsonParseState* pState);
static bool CORparseBoolean(const char*& current, CORvar& value, CORjsonParseState* pState);
static bool CORparseNull   (const char*& current, CORvar& value, CORjsonParseState* pState);
static bool CORparseValue  (const char*& current, CORvar& value, CORjsonParseState* pState);

static void CORskipWhitespace(const char*& current);
static bool CORpopulateError(CORvar* pInfo, const CORstring& Error, int Position);

bool CORparseJson(const char* pData, CORvar* pOutput);

bool CORparseJson(const CORstring& Data, CORvar* pOutput){
   COR_FUNCTION(CORparseJson-String);
   return CORparseJson(Data.c_str(), pOutput);
}

// Entry function to parse JSON
bool CORparseJson(const char* pData, CORvar* pOutput) {
   COR_FUNCTION(CORparseJson);
   CORjsonParseState State;
   const char* current = pData;
   CORskipWhitespace(current);
   if (*current == 0)                             { return CORpopulateError(pOutput, "Empty string", 0);                   }
   if (!CORparseValue(current, *pOutput, &State)) { return CORpopulateError(pOutput, State.ErrorMessage, current - pData); }
   CORskipWhitespace(current);  
   if (*current != '\0'){
      return CORpopulateError(pOutput, "Unexpected trailing content.", current-pData);
   } 
   return true;
}

static bool CORpopulateError(CORvar* pInfo, const CORstring& Error, int Position){
   COR_FUNCTION(CORpopulateError);
   pInfo->reset();
   (*pInfo) = "Error parsing JSON: " + Error + " Position: " + CORintToString(Position);
   //(*pInfo)["position"] = Position;
   return false;
}

// Determine the type of JSON data at the current position and parse it
static bool CORparseValue(const char*& current, CORvar& output, CORjsonParseState* pState) {
   CORskipWhitespace(current);
   switch (*current) {
   case '{' :        return CORparseObject (current,output,pState);
   case '[' :        return CORparseArray  (current,output,pState);
   case '\'':
   case '"' :        return CORparseString (current,output,pState);
   case 't' :
   case 'f' :        return CORparseBoolean(current,output,pState);
   case 'n' :        return CORparseNull   (current,output,pState);
   case '-':
   case '0': case '1': case '2': case '3': case '4':
   case '5': case '6': case '7': case '8': case '9':
                     return CORparseNumber(current, output, pState);
   default: 
      COR_ERR("Unexpected character in JSON");
      pState->ErrorMessage = CORstring("Unexpected character '") + *current + "'"; 
      return false;
   }
}

// Utility function to skip whitespace in the JSON input
static void CORskipWhitespace(const char*& i) {
    while (*i == ' ' || *i == '\n' || *i == '\r' || *i == '\t') { ++i;}
}

// Placeholder implementations for specific parsing functions
static bool CORparseObject(const char*& current, CORvar& output, CORjsonParseState* pState) {
   COR_FUNCTION(CORparseObject);
   current++;  // Skip the '{'
   output.setMapType();  // Set the type to Map (or Object)
   while (*current) {
      CORskipWhitespace(current);
      if (*current == '}') {  // Check for end of object
         current++;  // Skip the '}'
         return true;
      }
      // Parse the key (must be a string)
      CORvar key;
      if (!CORparseString(current, key, pState)) {
         return false;  // Failed to parse the key
      }
      CORskipWhitespace(current);
      // Expecting colon after the key
      if (*current != ':') { 
         pState->ErrorMessage = "Missing colon after key";
         return false;  
      }
      current++;  // Skip the colon
      CORskipWhitespace(current);
      if (!CORparseValue(current, output[key.asString()], pState)) {
         return false;  // Failed to parse the value
      }
      CORskipWhitespace(current);
      if (*current == ',') {
         current++;  // Skip the comma and continue
      } else if (*current != '}') {
         return false;  // Missing comma or end of object brace
      }
   }
   return false;  // Didn't find the closing '}'
}

static bool CORparseArray(const char*& current, CORvar& output, CORjsonParseState* pState) {
   COR_FUNCTION(CORparseArray);
   if (*current != '[') { return false; }
   current++;  // Skip the '['
   output.setArrayType();  // Set the type to Array
   while (*current) {
      CORskipWhitespace(current);
      if (*current == ']') {  // Check for end of array
         current++;  // Skip the ']'
         return true;
      }
      CORvar& Item = output.push_back();
      if (!CORparseValue(current, Item, pState)) {
         return false;  // Failed to parse the item
      }
      CORskipWhitespace(current);
      if (*current == ',') {
         current++;  // Skip the comma
      } else if (*current != ']') {
         pState->ErrorMessage = "Missing comma or end of array bracket";
         return false;  
      }
   }
   pState->ErrorMessage = "Unable to find closing ]";
   return false; 
}

// Converts a single hexadecimal character to its decimal value
static bool CORhexCharToValue(char c, unsigned int& value) {
   COR_VAR(c);
   if (c >= '0' && c <= '9') { value = c - '0'; } else 
   if (c >= 'A' && c <= 'F') { value = 10 + (c - 'A'); } else 
   if (c >= 'a' && c <= 'f') { value = 10 + (c - 'a'); } else {
     return false; // Non-hexadecimal character
   }
   COR_VAR(value);
   return true;
}

// Converts a Unicode code point to a UTF-8 encoded string
static bool CORunicodeToUtf8(unsigned int codepoint, CORstring& output) {
   if (codepoint < 0x80) { 
      output += static_cast<char>(codepoint); } else 
   if (codepoint < 0x800) {
      output += static_cast<char>(192 + (codepoint / 64)); 
      output += static_cast<char>(128 + (codepoint % 64)); } else 
   if (codepoint < 0x10000) {
      output += static_cast<char>(224 + (codepoint / 4096));
      output += static_cast<char>(128 + ((codepoint / 64) % 64));
      output += static_cast<char>(128 + (codepoint % 64));} else 
   if (codepoint < 0x110000) {
      output += static_cast<char>(240 +  (codepoint / 262144));
      output += static_cast<char>(128 + ((codepoint / 4096) % 64));
      output += static_cast<char>(128 + ((codepoint / 64) % 64));
      output += static_cast<char>(128 + (codepoint % 64));
   }
   return true;
}

// Parses a Unicode escape sequence from a JSON string
static bool CORparseUnicode(const char*& current, CORstring& output, CORjsonParseState* pState) {
   COR_FUNCTION(CORparseUnicode);
   unsigned int codepoint = 0;
   for (int i = 0; i < 4; i++) {
      unsigned int digitValue = 0;
      if (!CORhexCharToValue(*current++, digitValue)) {
         pState->ErrorMessage = "Invalid hexadecimal digit";
         return false;  
      }
      codepoint = (codepoint << 4) | digitValue;
   }
   COR_VAR(codepoint);
   return CORunicodeToUtf8(codepoint, output);
}

static bool CORparseString(const char*& current, CORvar& output, CORjsonParseState* pState) {
   COR_FUNCTION(CORparseString);
   char quoteType = *current;
   current++; // Skip the opening quote
   CORstring result;
   while (*current != quoteType && *current != '\0') {
      if (*current == '\\') { // Handle escape sequences
         current++; // Move past the backslash
         switch (*current) {
            case '"':  result += '"'; break;
            case '\\': result += '\\'; break;
            case '/':  result += '/'; break;
            case 'b':  result += '\b'; break;
            case 'f':  result += '\f'; break;
            case 'n':  result += '\n'; break;
            case 'r':  result += '\r'; break;
            case 't':  result += '\t'; break;
            case 'u': { // Unicode sequence (e.g., \u0123)
               current+=1;
               if (!CORparseUnicode(current, result, pState)){
                  return false;
               }
               current--;
               break;
            }
            default:
               CORstring BadSequence = current;
               BadSequence = BadSequence.substr(0, 1);
               CORstring Snippet = current;
               if (Snippet.size() > 30) { Snippet = Snippet.substr(0, 30); }
               pState->ErrorMessage = COR_T("Invalid escape sequence \\") + BadSequence + COR_T(" near \\") + Snippet;
               return false; // Invalid escape sequence
         }
      } else {
         result += *current;
      }
      current++;
   }
   if (*current != quoteType) {
      pState->ErrorMessage = "Missing closing quote";
      return false;
   }
   current++; // Skip the closing quote
   output = result; // Set the output CORvar to the parsed string
   return true;
}

static bool CORparseNumber(const char*& current, CORvar& output, CORjsonParseState* pState) {
   COR_FUNCTION(CORparseNumber);
   CORstring numberStr;
   bool hasFraction = false;
   bool hasExponent = false;
   if (*current == '-') { numberStr += *current++;}
   // Parse the integer part
   while (isdigit(*current)) { numberStr += *current++;}
   // Parse the fractional part
   if (*current == '.') {
      hasFraction = true;
      numberStr += *current++;
      while (isdigit(*current)) {numberStr += *current++;}
   }
   if (*current == 'e' || *current == 'E') {
      hasExponent = true;
      numberStr += *current++;
      if (*current == '+' || *current == '-') { numberStr += *current++; }
      while (isdigit(*current)) { numberStr += *current++;}
   }
   COR_TRC("Convert the CORstring to a numerical type using C standard library functions");
   char* endPtr;
   if (hasFraction || hasExponent) {
      double number = strtod(numberStr.c_str(), &endPtr);
      COR_VAR(number);
      if (*endPtr == '\0') { // Ensure entire string was valid
         output = number;
      } else {
         pState->ErrorMessage = "Unable to parse double";
         return false; // Parsing error occurred
      }
   } else {
      long long number = strtoll(numberStr.c_str(), &endPtr, 10);
      COR_VAR(number);
      if (*endPtr == '\0') { // Ensure entire string was valid
         output = number;
      } else {
         pState->ErrorMessage = "Unable to parse integer";
         return false; // Parsing error occurred
      }
   }
   return true;
}

static bool CORparseBoolean(const char*& current, CORvar& output, CORjsonParseState* pState) {
   COR_FUNCTION(CORparseBoolean);
   static const CORstring trueLiteral = "true";
   static const CORstring falseLiteral = "false";
   if (strncmp(current, trueLiteral.c_str(), trueLiteral.size()) == 0 && !isalnum(current[trueLiteral.size()])) {
      output = true;
      current += trueLiteral.size(); // Move past the 'true' literal
      return true;
   } else if (strncmp(current, falseLiteral.c_str(), falseLiteral.size()) == 0 && !isalnum(current[falseLiteral.size()])) {
      output = false;
      current += falseLiteral.size(); // Move past the 'false' literal
      return true;
   }
   pState->ErrorMessage = "Not a valid boolean";
   return false;
}

static bool CORparseNull(const char*& current, CORvar& output, CORjsonParseState* pState) {
   COR_FUNCTION(CORparseNull);
   static const CORstring nullLiteral = "null";
   if (strncmp(current, nullLiteral.c_str(), nullLiteral.size()) == 0 && !isalnum(current[nullLiteral.size()])) {
      output.reset(); // Set CORvar to null or clear it
      current += nullLiteral.size(); // Move past the 'null' literal
      return true;
   }
   pState->ErrorMessage = "Not a valid null";
   return false; // Not a valid null
}
