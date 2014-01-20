%include {
#include <cassert>
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

%token_type {Lex*}
%token_destructor {delete $$;}

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

%type simpleStmt {AST::SimpleStmt*}
%destructor simpleStmt {delete $$;}
simpleStmt(A) ::= expr(B) SEM. {A = AST::SimpleStmt::Create(B);}

%type expr {AST::Expr*}
%destructor expr {delete $$;}
expr(A) ::= STRING(B) . {A = new AST::String(B->loc, B->str); delete B;}
expr(A) ::= INTEGER(B) . {A = new AST::Integer(B->loc, B->str); delete B;}
expr(A) ::= DOUBLE(B) . {A = new AST::Double(B->loc, B->str); delete B;}
expr(A) ::= expr(B) PLUS expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::PLUS);}
expr(A) ::= MINUS expr(B) . [UMINUS] {A = AST::SingleOperExpr::Create(B, AST::SingleOperExpr::NEG);}

