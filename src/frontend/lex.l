%{
#include "ParserDef.h"
#include "Parser.tab.h"
#include "AST.h"
#include <vector>
#include <string>
std::vector<char> sb;
inline AST::Location getLoc()
{
	return {YY_CURRENT_BUFFER_LVALUE.yy_bs_lineno, YY_CURRENT_BUFFER_LVALUE.yy_bs_column};
}
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

{INTEGER}						{yylval = AST::Integer(getLoc(), yytext); return yytokentype::LITERAL;}
{DOUBLE}						{yylval = AST::Double(getLoc(), yytext); return yytokentype::LITERAL;}

<INITIAL>\"					{ sloc = getLoc(); BEGIN S; sb.clear();}
<S>{NEWLINE}		{/* issueError(new NewlineInStrError(sloc, MiscUtils.quote(buffer.toString())));*/}
<S><<EOF>>			{/* issueError(new UntermStrError(sloc, MiscUtils.quote(buffer.toString()))); yybegin(YYINITIAL);*/}
<S>\"				{BEGIN INITIAL; yylval = AST::String(std::string(sb.begin(), sb.end())); return yytokentype::LITERAL;}
<S>"\\n"			{sb.push_back('\n');}
<S>"\\t"			{sb.push_back('\t');}
<S>"\\\""			{sb.push_back('\"');}
<S>"\\\\"			{sb.push_back('\\');}
<S>.				{sb.push_back(yytext[0]);}

"if"							{yylval = new AST::Keyword(AST::Keyword::Type::IF); return yytokentype::IF;}
"func"							{yylval = new AST::Keyword(AST::Keyword::Type::FUNC); return yytokentype::FUNC;}
"state"							{yylval = new AST::Keyword(AST::Keyword::Type::STATE); return yytokentype::STATE;}
"else"							{yylval = new AST::Keyword(AST::Keyword::Type::ELSE); return yytokentype::ELSE;}
"while"							{yylval = new AST::Keyword(AST::Keyword::Type::WHILE); return yytokentype::WHILE;}
"break"							{yylval = new AST::Keyword(AST::Keyword::Type::BREAK); return yytokentype::BREAK;}
{IDENTIFIER}					{yylval = new AST::Identifier(yytext); return yytokentype::IDENTIFIER;}
%%
