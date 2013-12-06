%{
#define YYSTYPE AST::Node
%}
%token IF ELSE WHILE BREAK FUNC STATE IDENTIFIER

%left GOPER(||)
%left GOPER(&&) 
%left GOPER(==) GOPER(!=)
%left GOPER(<=) GOPER(>=) "<" ">"
%left "+" "-"
%left "*" "/" "%"
%nonassoc UMINUS "!" 
%left "[" "." 
%nonassoc ")"
%nonassoc ELSE

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

SimpleStmt	:	Expr ";"
		;

ForStmt		:	FOR "(" IDENTIFIER ":" Expr ")" Stmt
		;

WhileStmt	:	WHILE "(" Expr ")" Stmt
		;

StmtBlock	:	"{" StmtList "}"
		;

Expr		:	LITERAL
	  		|	ListLiteral
			|	StateDef
			|	FuncDef
			|	CallExpr
			|	SimpleExpr
		;

ExprList	:	ExprList Expr
		;

ListLiteral	:	"[" ExprList "]"
		;

IDs			:	IDs IDENTIFIER
	  		|
		;

StateDef	:	STATE IDs StmtBlock
		;

FuncDef		:	FUNC IDs "(" IDs ")" StmtBlock
		;

CallExpr	:	IDENTIFIER "(" ExprList ")"
		;

SimpleExpr	:	Expr "+" Expr
			|	Expr "-" Expr
			|	Expr "*" Expr
			|	Expr "/" Expr
			|	Expr "%" Expr
			|	Expr GOPER(<=) Expr
			|	Expr GOPER(>=) Expr
			|	Expr "<" Expr
			|	Expr ">" Expr
			|	Expr GOPER(==) Expr
			|	Expr GOPER(!=) Expr
			|	Expr GOPER(&&) Expr
			|	Expr GOPER(||) Expr
			|	"!" Expr
			|	"-" Expr			%prec UMINUS
		;
%%
