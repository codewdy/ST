%{
	typedef AST::Node YYSTYPE;
	typedef AST::Location YYLTYPE;
	int yywrap() {return 1;}
%}

NEWLINE				(\r|\n|\r\n)
DIGIT				([0-9])
HEX_DIGIT			([0-9A-Fa-f])
HEX_INTEGER			(0[Xx]{HEX_DIGIT}+)
DEC_INTEGER			({DIGIT}+)
INTEGER				({HEX_INTEGER}|{DEC_INTEGER})
DOUBLE				((([0-9]+"."[0-9]*|[0-9]*"."[0-9]+)([eE][0-9]+)?)|([0-9]+[eE][0-9]+))
IDENTIFIER			([_A-Za-z][_0-9A-Za-z]*)
OPERATOR			("+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"."|","|";"|"!"|"("|")"|"["|"]"|"{"|"}"|"&&"|"||"|"<="|">="|"=="|"!=")
S_COMMENT			("//"[^\r\n]*{NEWLINE})
MULTILINE_COMMENT	("/*"([^/]*[^*/]"/"|"/")*[^/]*"*/")
WHITESPACE			([ \t]+)

%x S

%%
{WHITESPACE}					{}
{S_COMMENT}						{}
{MULTILINE_COMMENT}				{}
{NEWLINE}						{}

{OPERATOR}						{yylval = new AST::Oper(yylloc, gOper(yytext)); return gOper(yytext);}

{INTEGER}						{yylval = AST::Literal::BuildInteger(yylloc, yytext); return LITERAL;}
{DOUBLE}						{yylval = AST::Literal::BuildDOUBLE(yylloc, yytext); return LITERAL;}

<INITIAL>\"					{ sloc = getLocation(); yybegin(S); buffer = new StringBuilder();}
<S>{NEWLINE}		{ issueError(new NewlineInStrError(sloc, MiscUtils.quote(buffer.toString())));}
<S><<EOF>>			{ issueError(new UntermStrError(sloc, MiscUtils.quote(buffer.toString()))); yybegin(YYINITIAL);}
<S>\"				{ yybegin(YYINITIAL); return StringConst(buffer.toString(), sloc);}
<S>"\\n"			{ buffer.append('\n');}
<S>"\\t"			{ buffer.append('\t');}
<S>"\\\""			{ buffer.append('"');}
<S>"\\\\"			{ buffer.append('\\');}
<S>.				{ buffer.append(yytext());}

"if"							{yylval = new AST::Keyword(IF); return IF;}
"func"							{yylval = new AST::Keyword(FUNC); return FUNC;}
"state"							{yylval = new AST::Keyword(STATE); return STATE;}
"else"							{yylval = new AST::Keyword(ELSE); return ELSE;}
"while"							{yylval = new AST::Keyword(WHILE); return WHILE;}
"break"							{yylval = new AST::Keyword(BREAK); return BREAK;}
{IDENTIFIER}					{yylval = new AST::Identifier(yytext); }
%%
