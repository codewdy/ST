%include {
#include "ParserDef.h"
}
%left OR .
%left AND .
%left EQ NE .
%left LE GE LT GT .
%left PLUS MINUS .
%left MUL DIV MOD .
%nonassoc NOT .
%left RMC DOT .
%nonassoc RLC .
%nonassoc ELSE .

%start_symbol program

%token_type {Lex}

%type program {AST::Program*}
program(A) ::= stmtList(B). {A = AST::Program::Create(B);}

%type stmtList {AST::StmtList*}
%destructor stmtList {delete $$;}
stmtList(A) ::= . {A = AST::StmtList::Create();}
stmtList(A) ::= stmtList(B) stmt(C). {A = AST::StmtList::Create(B, C);}

%type stmt {AST::Stmt*}
%destructor stmt {delete $$;}
stmt(A) ::= simpleStmt(B). {A = B;}
stmt(A) ::= forStmt(B). {A = B;}
stmt(A) ::= whileStmt(B). {A = B;}
stmt(A) ::= stmtBlock(B). {A = B;}

%type simpleStmt {AST::SimpleStmt}
%destructor simpleStmt {delete $$;}
simpleStmt(A) ::= expr(B) SEM. {A = SimpleStmt::Create(B);}

%type expr {AST::Expr}
%destructor expr {delete $$;}
expr(A) ::= STRING(B) . {A = AST::String::Create(B.loc, B.str);}
expr(A) ::= INTEGER(B) . {A = AST::Integer::Create(B.loc, B.str);}
expr(A) ::= DOUBLE(B) . {A = AST::Double::Create(B.loc, B.str);}
expr(A) ::= expr(B) PLUS expr(C) . {A = AST::DoubleOperExpr(B, C, AST::DoubleOperExpr::PLUS);}
expr(A) ::= MINUS expr(B) . [UMINUS] {A = AST::SingleOperExpr(B, AST::SingleOperExpr::UMINUS);}

