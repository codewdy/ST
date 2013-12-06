%{
	#define YYSTYPE std::shared_ptr<AST>
	int yywrap() {return 1;}
%}

NEWLINE				= (\r|\n|\r\n)
DIGIT 				= ([0-9])
HEX_DIGIT 			= ([0-9A-Fa-f])
HEX_INTEGER			= (0[Xx]{HEX_DIGIT}+)
DEC_INTEGER			= ({DIGIT}+)
INTEGER				= ({HEX_INTEGER}|{DEC_INTEGER})
DOUBLE				= ((([0-9]+"."[0-9]* | [0-9]*"."[0-9]+)([eE][0-9]+)?) | ([0-9]+[eE][0-9]+))
IDENTIFIER			= ([_A-Za-z][_0-9A-Za-z]*)
SINGLE_OP			= ("+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"."|","|";"|"!"|"("|")"|"["|"]"|"{"|"}")
DOUBLE_OP			= ("&&" | "||" | "<=" | ">=" | "==" | "!=")
S_COMMENT			= ("//"[^\r\n]*{NEWLINE})
MULTILINE_COMMENT	= ("/*"([^/]*[^*/]"/" | "/")*[^/]*"*/")
WHITESPACE			= ([ \t]+)
