%{
	typedef AST::AST::Node YYSTYPE;
	typedef AST::AST::Location YYLTYPE;
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
	Ignore
{WHITESPACE}					{}
{S_COMMENT}						{}
{MULTILINE_COMMENT}				{}
{NEWLINE}						{}

	Operator
{OPERATOR}						{yylval = new AST::Oper(yylloc, gOper(yytext)); return gOper(yytext);}
%%
