%{
#include "ParserDef.h"
#include "Parser.tab.h"
#include <vector>
#include <string>
std::vector<char> sb;
inline AST::Location getLoc()
{
	return AST::Location(AST::currentSource, yylineno);
}
AST::Location sloc;
%}

NEWLINE				(\r|\n|\r\n)
DIGIT				([0-9])
HEX_DIGIT			([0-9A-Fa-f])
HEX_INTEGER			(0[Xx]{HEX_DIGIT}+)
BIN_INTEGER			(0[Bb][01]+)
DEC_INTEGER			({DIGIT}+)
INTEGER				({BIN_INTEGER}{HEX_INTEGER}|{DEC_INTEGER})
DOUBLE				((([0-9]+"."[0-9]*|[0-9]*"."[0-9]+)([eE][0-9]+)?)|([0-9]+[eE][0-9]+))
IDENTIFIER			([_A-Za-z][_0-9A-Za-z]*)
OPERATOR			("+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"."|","|";"|"!"|"("|")"|"["|"]"|"{"|"}")
S_COMMENT			("//"[^\r\n]*{NEWLINE})
MULTILINE_COMMENT	("/*"([^/]*[^*/]"/"|"/")*[^/]*"*/")
WHITESPACE			([ \t]+)

%option noyywrap
%x S

%%
{WHITESPACE}					{}
{S_COMMENT}						{}
{MULTILINE_COMMENT}				{}
{NEWLINE}						{}

{OPERATOR}						{yylval = new AST::Oper(getLoc(), yytext); return yytext[0];}
"&&"							{yylval = new AST::Oper(getLoc(), yytext); return yytokentype::AND;}
"||"							{yylval = new AST::Oper(getLoc(), yytext); return yytokentype::OR;}
"<="							{yylval = new AST::Oper(getLoc(), yytext); return yytokentype::LE;}
">="							{yylval = new AST::Oper(getLoc(), yytext); return yytokentype::GE;}
"=="							{yylval = new AST::Oper(getLoc(), yytext); return yytokentype::EQ;}
"!="							{yylval = new AST::Oper(getLoc(), yytext); return yytokentype::NE;}

{INTEGER}						{yylval = new AST::Integer(getLoc(), yytext); return yytokentype::LITERAL;}
{DOUBLE}						{yylval = new AST::Double(getLoc(), yytext); return yytokentype::LITERAL;}

<INITIAL>\"					{ sloc = getLoc(); BEGIN S; sb.clear();}
<S>{NEWLINE}		{/* issueError(new NewlineInStrError(sloc, MiscUtils.quote(buffer.toString())));*/}
<S><<EOF>>			{/* issueError(new UntermStrError(sloc, MiscUtils.quote(buffer.toString()))); yybegin(YYINITIAL);*/}
<S>\"				{BEGIN INITIAL; yylval = new AST::String(sloc, std::string(sb.begin(), sb.end())); return yytokentype::LITERAL;}
<S>"\\n"			{sb.push_back('\n');}
<S>"\\t"			{sb.push_back('\t');}
<S>"\\\""			{sb.push_back('\"');}
<S>"\\\\"			{sb.push_back('\\');}
<S>.				{sb.push_back(yytext[0]);}

"if"							{yylval = new AST::Keyword(getLoc(), AST::Keyword::Type::IF); return yytokentype::IF;}
"else"							{yylval = new AST::Keyword(getLoc(), AST::Keyword::Type::ELSE); return yytokentype::ELSE;}
"func"							{yylval = new AST::Keyword(getLoc(), AST::Keyword::Type::FUNC); return yytokentype::FUNC;}
"state"							{yylval = new AST::Keyword(getLoc(), AST::Keyword::Type::STATE); return yytokentype::STATE;}
"for"							{yylval = new AST::Keyword(getLoc(), AST::Keyword::Type::FOR); return yytokentype::FOR;}
"while"							{yylval = new AST::Keyword(getLoc(), AST::Keyword::Type::WHILE); return yytokentype::WHILE;}
"break"							{yylval = new AST::Keyword(getLoc(), AST::Keyword::Type::BREAK); return yytokentype::BREAK;}
{IDENTIFIER}					{yylval = new AST::Identifier(getLoc(), yytext); return yytokentype::IDENTIFIER;}
%%

