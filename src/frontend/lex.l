%{
#include "ParserDef.h"
#include <vector>
#include <string>
std::vector<char> sb;
#define MakeLex(type) return new Lex({YYText(), type, {0, lineno()}})
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
%option noyywrap
%option c++
%x S

%%
{WHITESPACE}					{}
{S_COMMENT}						{}
{MULTILINE_COMMENT}				{}
{NEWLINE}						{}

"+"                             {MakeLex(PLUS);}
"-"                             {MakeLex(MINUS);}
"*"                             {MakeLex(MUL);}
"/"                             {MakeLex(DIV);}
"%"                             {MakeLex(MOD);}
"="                             {MakeLex(ASG);}
"."                             {MakeLex(DOT);}
","                             {MakeLex(CMA);}
";"                             {MakeLex(SEM);}
"("                             {MakeLex(LLC);}
")"                             {MakeLex(RLC);}
"["                             {MakeLex(LMC);}
"]"                             {MakeLex(RMC);}
"{"                             {MakeLex(LBC);}
"}"                             {MakeLex(RBC);}
">"                             {MakeLex(GT);}
"<"                             {MakeLex(LT);}
">="                            {MakeLex(GE);}
"<="                            {MakeLex(LE);}
"=="                            {MakeLex(EQ);}
"!="                            {MakeLex(NE);}
"!"                             {MakeLex(NOT);}
"&&"                            {MakeLex(AND);}
"||"                            {MakeLex(OR);}

{INTEGER}						{yylval = new AST::Integer(getLoc(), yytext); return yytokentype::LITERAL;}
{DOUBLE}						{yylval = new AST::Double(getLoc(), yytext); return yytokentype::LITERAL;}

<INITIAL>\"                     { sloc = lineno(); BEGIN S; sb.clear();}
<S>{NEWLINE}                    {/* issueError(new NewlineInStrError(sloc, MiscUtils.quote(buffer.toString())));*/}
<S><<EOF>>                      {/* issueError(new UntermStrError(sloc, MiscUtils.quote(buffer.toString()))); yybegin(YYINITIAL);*/}
<S>\"                           {BEGIN INITIAL; return new Lex({std::string(sb.begin(), sb.end()), STRING, {0, sloc}});}
<S>"\\n"                        {sb.push_back('\n');}
<S>"\\t"                        {sb.push_back('\t');}
<S>"\\\""                       {sb.push_back('\"');}
<S>"\\\\"                       {sb.push_back('\\');}
<S>.                            {sb.push_back(YYText()[0]);}

"if"                            {MakeLex(IF);}
"else"                          {MakeLex(ELSE);}
"func"                          {MakeLex(FUNC);}
"state"                         {MakeLex(STATE);}
"for"                           {MakeLex(FOR);}
"while"                         {MakeLex(WHILE);}
"break"                         {MakeLex(BREAK);}
{IDENTIFIER}					{MakeLex(IDENTIFIER);}
.                               {/*Error*/}
%%

