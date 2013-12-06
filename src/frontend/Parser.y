%{
#define YYSTYPE AST::Node
%}
%token IF ELSE FOR WHILE BREAK FUNC STATE IDENTIFIER LITERAL

%left OR
%left AND 
%left EQ NE
%left LE GE '<' '>'
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS '!' 
%left '[' '.' 
%nonassoc ')'
%nonassoc ELSE

%start Program

%%
Program		:	StmtList
		 ;
StmtList	:	StmtList Stmt
		 	|	Stmt
		;
Stmt		:	SimpleStmt
	  		|	ForStmt
			|	WhileStmt
			|	StmtBlock
		;

SimpleStmt	:	Expr ';'
		;

ForStmt		:	FOR '(' IDENTIFIER ':' Expr ')' Stmt
		;

WhileStmt	:	WHILE '(' Expr ')' Stmt
		;

StmtBlock	:	'{' StmtList '}'
		;

Expr		:	LITERAL
	  		|	ListLiteral
			|	StateDef
			|	FuncDef
			|	CallExpr
			|	SimpleExpr
			|	LVALUE
		;

ExprList	:	ExprList  ',' Expr
		 	|
		;

ListLiteral	:	'[' ExprList ']'
		;

IDs			:	IDs IDENTIFIER
	  		|
		;

StateDef	:	STATE IDs StmtBlock
		;

FuncDef		:	FUNC IDs '(' IDs ')' StmtBlock
		;

CallExpr	:	Expr '(' ExprList ')'
		;

SimpleExpr	:	Expr '+' Expr
			|	Expr '-' Expr
			|	Expr '*' Expr
			|	Expr '/' Expr
			|	Expr '%' Expr
			|	Expr LE Expr
			|	Expr GE Expr
			|	Expr '<' Expr
			|	Expr '>' Expr
			|	Expr EQ Expr
			|	Expr NE Expr
			|	Expr AND Expr
			|	Expr OR Expr
			|	LVALUE '=' Expr
			|	'!' Expr
			|	'-' Expr			%prec UMINUS
		;

LVALUE		:	IDENTIFIER
			|	Expr '.' IDENTIFIER
			|	Expr '[' Expr ']'
		;
%%
