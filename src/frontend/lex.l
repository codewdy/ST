%{
#include "Parser.tab.h"
#include <vector>
#define YYSTYPE AST::Node
#define YYLTYPE AST::Location
std::vector<char> sb;
int yywrap() {return 1;}
%}

NEWLINE				(\r|\n|\r\n)
DIGIT				([0-9])
HEX_DIGIT			([0-9A-Fa-f])
HEX_INTEGER			(0[Xx]{HEX_DIGIT}+)
DEC_INTEGER			([1-9]{DIGIT}*)
OCT_INTEGER			(0[0-7]*)
INTEGER				({HEX_INTEGER}|{DEC_INTEGER})
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

{OPERATOR}						{yylval = new AST::Oper(yylloc, yytext); return yytext[0];}
"&&"							{yylval = new AST::Oper(yylloc, yytext); return AND;}
"||"							{yylval = new AST::Oper(yylloc, yytext); return OR;}
"<="							{yylval = new AST::Oper(yylloc, yytext); return LE;}
">="							{yylval = new AST::Oper(yylloc, yytext); return GE;}
"=="							{yylval = new AST::Oper(yylloc, yytext); return EQ;}
"!="							{yylval = new AST::Oper(yylloc, yytext); return NE;}

{INTEGER}						{yylval = AST::Integer(yylloc, yytext); return LITERAL;}
{DOUBLE}						{yylval = AST::Double(yylloc, yytext); return LITERAL;}

<INITIAL>\"					{ sloc = yylloc; yybegin(S); sb.clear()}
<S>{NEWLINE}		{/* issueError(new NewlineInStrError(sloc, MiscUtils.quote(buffer.toString())));*/}
<S><<EOF>>			{/* issueError(new UntermStrError(sloc, MiscUtils.quote(buffer.toString()))); yybegin(YYINITIAL);*/}
<S>\"				{yybegin(INITIAL); yylval = AST::String(std::string(sb.begin(), sb.end())); return LITERAL;}
<S>"\\n"			{sb.push_back('\n');}
<S>"\\t"			{sb.push_back('\t');}
<S>"\\\""			{sb.push_back('\"');}
<S>"\\\\"			{sb.push_back('\\');}
<S>.				{sb.push_back(yytext[0]);}

"if"							{yylval = new AST::Keyword(IF); return IF;}
"func"							{yylval = new AST::Keyword(FUNC); return FUNC;}
"state"							{yylval = new AST::Keyword(STATE); return STATE;}
"else"							{yylval = new AST::Keyword(ELSE); return ELSE;}
"while"							{yylval = new AST::Keyword(WHILE); return WHILE;}
"break"							{yylval = new AST::Keyword(BREAK); return BREAK;}
{IDENTIFIER}					{yylval = new AST::Identifier(yytext); }
%%
