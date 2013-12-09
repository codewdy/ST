%{
#include "ParserDef.h"
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
			 	{$$ = AST::Program::Create((AST::StmtList*)$1);}
	 ;
StmtList	:	StmtList Stmt
			 	{$$ = AST::StmtList::Create((AST::StmtList*)$1, (AST::Stmt*)$2);}
		 	|
			 	{$$ = AST::StmtList::Create();}
		;
Stmt		:	SimpleStmt
	  		|	ForStmt
			|	WhileStmt
			|	StmtBlock
		;

SimpleStmt	:	Expr ';'
				{$$ = AST::SimpleStmt::Create((AST::Expr*)$1, (AST::Oper*)$2);}
		;

ForStmt		:	FOR '(' IDENTIFIER ':' Expr ')' Stmt
				{$$ = AST::ForStmt::Create((AST::Keyword*)$1, (AST::Oper*)$2, 
					(AST::Identifier*)$3, (AST::Oper*)$4, (AST::Expr*)$5, 
					(AST::Oper*)$6, (AST::Stmt*)$7);}
		;

WhileStmt	:	WHILE '(' Expr ')' Stmt
				{$$ = AST::WhileStmt::Create((AST::Keyword*)$1, (AST::Oper*)$2, 
					(AST::Expr*)$3, (AST::Oper*)$4, (AST::Stmt*)$5);}
		;

StmtBlock	:	'{' StmtList '}'
		  		{$$ = AST::StmtBlock::Create((AST::Oper*)$1, (AST::StmtList*)$2, (AST::Oper*)$3);}
		;

Expr		:	LITERAL
			|	StateDef
			|	FuncDef
			|	CallExpr
			|	SimpleExpr
			|	ListExpr
			|	LValue
		;

ExprList	:	ExprListHelper
			|
				{$$ = AST::ExprList::Create();}
		;
ExprListHelper:	ExprListHelper ',' Expr
		 		{$$ = AST::ExprList::Create((AST::ExprList*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
		 	|	Expr
		 		{$$ = AST::ExprList::Create((AST::Expr*)$1);}
			;

ListExpr	:	'[' ExprList ']'
		 		{$$ = AST::ListExpr::Create((AST::Oper*)$1, (AST::ExprList*)$2, (AST::Oper*)$3);}
		;

IDs			:	IDsHelper
	  		|
				{$$ = AST::IDs::Create();}
		;

IDsHelper	:	IDsHelper ',' IDENTIFIER
	  			{$$ = AST::IDs::Create((AST::IDs*)$1, (AST::Oper*)$2, (AST::Identifier*)$3);}
			|	IDENTIFIER
				{$$ = AST::IDs::Create((AST::Identifier*)$1);}
		;

StateDef	:	STATE IDs StmtBlock
		 		{$$ = AST::StateDef::Create((AST::Keyword*)$1, (AST::IDs*)$2, (AST::StmtBlock*)$3);}
		;

FuncDef		:	FUNC IDs '(' IDs ')' StmtBlock
		 		{$$ = AST::FuncDef::Create((AST::Keyword*)$1, (AST::IDs*)$2, (AST::Oper*)$3, 
					(AST::IDs*)$4, (AST::Oper*)$5, (AST::StmtBlock*)$6);}
		;

CallExpr	:	Expr '(' ExprList ')'
				{$$ = AST::CallExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::ExprList*)$3, (AST::Oper*)$4);}
		;

SimpleExpr	:	Expr '+' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr '-' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr '*' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr '/' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr '%' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr LE Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr GE Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr '<' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr '>' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr EQ Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr NE Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr AND Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	Expr OR Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	LValue '=' Expr
				{$$ = AST::DoubleOperExpr::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3);}
			|	'!' Expr
				{$$ = AST::SingleOperExpr::Create((AST::Oper*)$1, (AST::Expr*)$2);}
			|	'-' Expr			%prec UMINUS
				{$$ = AST::SingleOperExpr::Create((AST::Oper*)$1, (AST::Expr*)$2);}
		;

LValue		:	IDENTIFIER
				{$$ = AST::VarLValue::Create((AST::Identifier*)$1);}
			|	Expr '.' IDENTIFIER
				{$$ = AST::VarLValue::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Identifier*)$3);}
			|	Expr '[' Expr ']'
				{$$ = AST::ArrayAtLValue::Create((AST::Expr*)$1, (AST::Oper*)$2, (AST::Expr*)$3, (AST::Oper*)$4);}
		;
%%
