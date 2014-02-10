%{
#include "ParserDef.h"
#include "Exception.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "Parser.h"
std::vector<char> sb;
std::unordered_map<int, Lex*> lexMap;
#define ST_MAKE_LEX_STR(str, type) do {\
    Lex* tmp = new Lex(str, type, AST::Location(nullptr, lineno()));\
    int ret = long(tmp) % 98765431;\
    while (ret++)\
        if (lexMap.insert(std::make_pair(ret, tmp)).second)\
            return ret;\
} while (0)

#define ST_MAKE_LEX(type) ST_MAKE_LEX_STR(YYText(), type)
int sloc;
%}

NEWLINE				(\r|\n|\r\n)
DIGIT				([0-9])
HEX_DIGIT			([0-9A-Fa-f])
HEX_INTEGER			(0[Xx]{HEX_DIGIT}+)
BIN_INTEGER			(0[Bb][01]+)
DEC_INTEGER			({DIGIT}+)
INTEGER				({BIN_INTEGER}|{HEX_INTEGER}|{DEC_INTEGER})
DOUBLE				((([0-9]+"."[0-9]*|[0-9]*"."[0-9]+)([eE][0-9]+)?)|([0-9]+[eE][0-9]+))
IDENTIFIER			([_A-Za-z][_0-9A-Za-z]*)
S_COMMENT			("//"[^\r\n]*{NEWLINE})
MULTILINE_COMMENT	("/*"([^/]*[^*/]"/"|"/")*[^/]*"*/")
WHITESPACE			([ \t]+)

%option outfile="Lexer.cpp" HEADER-FILE="Lexer.h"
%option c++
%x S

%%
{WHITESPACE}					{}
{S_COMMENT}						{}
{MULTILINE_COMMENT}				{}
{NEWLINE}						{yylineno++;}

"+"                             {ST_MAKE_LEX(PLUS);}
"-"                             {ST_MAKE_LEX(MINUS);}
"*"                             {ST_MAKE_LEX(MUL);}
"/"                             {ST_MAKE_LEX(DIV);}
"%"                             {ST_MAKE_LEX(MOD);}
"="                             {ST_MAKE_LEX(ASG);}
"."                             {ST_MAKE_LEX(DOT);}
","                             {ST_MAKE_LEX(CMA);}
":"                             {ST_MAKE_LEX(COL);}
";"                             {ST_MAKE_LEX(SEM);}
"("                             {ST_MAKE_LEX(LLC);}
")"                             {ST_MAKE_LEX(RLC);}
"["                             {ST_MAKE_LEX(LMC);}
"]"                             {ST_MAKE_LEX(RMC);}
"{"                             {ST_MAKE_LEX(LGC);}
"}"                             {ST_MAKE_LEX(RGC);}
">"                             {ST_MAKE_LEX(GT);}
"<"                             {ST_MAKE_LEX(LT);}
">="                            {ST_MAKE_LEX(GE);}
"<="                            {ST_MAKE_LEX(LE);}
"=="                            {ST_MAKE_LEX(EQ);}
"!="                            {ST_MAKE_LEX(NE);}
"!"                             {ST_MAKE_LEX(NOT);}
"&&"                            {ST_MAKE_LEX(AND);}
"||"                            {ST_MAKE_LEX(OR);}

{INTEGER}						{ST_MAKE_LEX(INTEGER);}
{DOUBLE}						{ST_MAKE_LEX(DOUBLE);}

<INITIAL>\"                     {sloc = lineno(); BEGIN S; sb.clear();}
<S>{NEWLINE}                    {ST_RAISE(Syntax, "", lineno());}
<S><<EOF>>                      {ST_RAISE(Syntax, "", lineno());}
<S>\"                           {BEGIN INITIAL; ST_MAKE_LEX_STR(std::string(sb.begin(), sb.end()), STRING);}
<S>"\\n"                        {sb.push_back('\n');}
<S>"\\t"                        {sb.push_back('\t');}
<S>"\\\""                       {sb.push_back('\"');}
<S>"\\\\"                       {sb.push_back('\\');}
<S>.                            {sb.push_back(YYText()[0]);}

"if"                            {ST_MAKE_LEX(IF);}
"else"                          {ST_MAKE_LEX(ELSE);}
"func"                          {ST_MAKE_LEX(FUNC);}
"state"                         {ST_MAKE_LEX(STATE);}
"for"                           {ST_MAKE_LEX(FOR);}
"while"                         {ST_MAKE_LEX(WHILE);}
"break"                         {ST_MAKE_LEX(BREAK);}
"return"                        {ST_MAKE_LEX(RETURN);}
"global"                        {ST_MAKE_LEX(GLOBAL);}
"null"                          {ST_MAKE_LEX(NULL_);}
{IDENTIFIER}					{ST_MAKE_LEX(IDENTIFIER);}
<<EOF>>                         {return 0;}
.                               {ST_RAISE(Syntax, "", lineno());}
%%

int yyFlexLexer::yywrap() { return 1; }
