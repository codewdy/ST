%extra_argument {AST::Program** ret}

%parse_failure {/*Raise(SyntaxError, TOKEN->loc);*/}

%include {
#include <cassert>
#include "ParserDef.h"
#include <unordered_map>
extern std::unordered_map<int, Lex*> lexMap;
}

%code {
#include <string>
#include <iostream>
#include <fstream>
#include "Exception.h"
#include "Lexer.h"
namespace Parser {
    AST::Program* CreateAST(std::string filename) {
        std::string* fn = new std::string(filename);
        void *parser = ParseAlloc(malloc);
        std::ifstream stream(filename.c_str());
        try {
            yyFlexLexer lexer(&stream);
            int tokenT;
            while (tokenT = lexer.yylex()) {
                Lex* token = lexMap[tokenT];
                lexMap.erase(tokenT);
                token->loc.str = fn;
                Parse(parser, token->type, token, 0);
            }
            AST::Program* ret;
            Parse(parser, 0, 0, &ret);
            ret->loc.str = fn;
            return ret;
        } catch (Exception::Exception e) {
            delete fn;
            ParseFree(parser, free);
            throw e;
        }
    }
}
}

%syntax_error {
//TODO: Add Error Control.
throw "Error";
}

%right ASG .
%left OR .
%left AND .
%left EQ NE .
%left LE GE LT GT .
%left PLUS MINUS .
%left MUL DIV MOD .
%nonassoc NEG NOT .
%left RMC DOT .
%nonassoc RLC .
%nonassoc ELSE .

%start_symbol program

%token_type {Lex*}
%token_destructor {delete $$;}

%type program {AST::Program*}
program(A) ::= stmtList(B). {*ret = A = new AST::Program(AST::Location(), B);}

%type stmtList {AST::StmtList*}
%destructor stmtList {delete $$;}
stmtList(A) ::= . {A = new AST::StmtList;}
stmtList(A) ::= stmtList(B) stmt(C). {A = new AST::StmtList(B, C);}

%type stmt {AST::Stmt*}
%destructor stmt {delete $$;}
stmt(A) ::= expr(B) SEM . {A = new AST::SimpleStmt(B->loc, B);}
stmt(A) ::= FOR(LOC) LLC lValue(B) COL expr(C) RLC stmt(D). {A = new AST::ForStmt(LOC->loc, B, C, D); delete LOC;}
stmt(A) ::= WHILE(LOC) LLC expr(B) RLC stmt(C) . {A = new AST::WhileStmt(LOC->loc, B, C); delete LOC;}
stmt(A) ::= IF(LOC) LLC expr(B) RLC stmt(C) . {A = new AST::IfStmt(LOC->loc, B, C); delete LOC;}
stmt(A) ::= IF(LOC) LLC expr(B) RLC stmt(C) ELSE stmt(D) . {A = new AST::IfStmt(LOC->loc, B, C, D); delete LOC;}
stmt(A) ::= stmtBlock(B) . {A = B;}
stmt(A) ::= BREAK(LOC) SEM . {A = new AST::BreakStmt(LOC->loc); delete LOC;}
stmt(A) ::= RETURN(LOC) expr(B) SEM . {A = new AST::ReturnStmt(LOC->loc, B); delete LOC;}
stmt(A) ::= RETURN(LOC) SEM . {A = new AST::ReturnStmt(LOC->loc); delete LOC;}

%type stmtBlock {AST::StmtBlock*}
%destructor stmtBlock {delete $$;}
stmtBlock(A) ::= LGC(LOC) stmtList(B) RGC . {A = new AST::StmtBlock(LOC->loc, B); delete LOC;}

%type expr {AST::Expr*}
%destructor expr {delete $$;}
//Literal Expr
expr(A) ::= STRING(B) . {A = new AST::String(B->loc, B->str); delete B;}
expr(A) ::= INTEGER(B) . {A = new AST::Integer(B->loc, B->str); delete B;}
expr(A) ::= DOUBLE(B) . {A = new AST::Double(B->loc, B->str); delete B;}
expr(A) ::= GLOBAL(B) . {A = new AST::GlobalExpr(B->loc); delete B;}
expr(A) ::= NULL_(B) . {A = new AST::NullExpr(B->loc); delete B;}
//LValue Expr
expr(A) ::= lValue(B) . {A = B;}
//Call Expr
expr(A) ::= expr(B) LLC(LOC) exprList(C) RLC . {A = new AST::CallExpr(LOC->loc, B, C); delete LOC;}
//Func Def Expr
expr(A) ::= FUNC(LOC) lValueList(B) LLC iDList(C) RLC stmtBlock(D) . {A = new AST::FuncDef(LOC->loc, B, C, D); delete LOC;}
//State Def Expr
expr(A) ::= STATE(LOC) lValueList(B) stmtBlock(C) . {A = new AST::StateDef(LOC->loc, B, C); delete LOC;}
//List Expr
expr(A) ::= LMC(LOC) exprList(B) RLC . {A = new AST::ListExpr(LOC->loc, B); delete LOC;}
//Simple Expr
expr(A) ::= LLC expr(B) RLC . {A = B;}
expr(A) ::= expr(B) PLUS(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::PLUS); delete LOC;}
expr(A) ::= expr(B) MINUS(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::MINUS); delete LOC;}
expr(A) ::= expr(B) MUL(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::MUL); delete LOC;}
expr(A) ::= expr(B) DIV(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::DIV); delete LOC;}
expr(A) ::= expr(B) MOD(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::MOD); delete LOC;}
expr(A) ::= expr(B) LT(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::LT); delete LOC;}
expr(A) ::= expr(B) GT(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::GT); delete LOC;}
expr(A) ::= expr(B) LE(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::LE); delete LOC;}
expr(A) ::= expr(B) GE(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::GE); delete LOC;}
expr(A) ::= expr(B) EQ(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::EQ); delete LOC;}
expr(A) ::= expr(B) NE(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::NE); delete LOC;}
expr(A) ::= expr(B) AND(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::AND); delete LOC;}
expr(A) ::= expr(B) OR(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::OR); delete LOC;}
expr(A) ::= lValue(B) ASG(LOC) expr(C) . {A = new AST::DoubleOperExpr(LOC->loc, B, C, AST::DoubleOperExpr::ASG); delete LOC;}
expr(A) ::= MINUS(LOC) expr(B) . [NEG] {A = new AST::SingleOperExpr(LOC->loc, B, AST::SingleOperExpr::NEG); delete LOC;}
expr(A) ::= NOT(LOC) expr(B) . {A = new AST::SingleOperExpr(LOC->loc, B, AST::SingleOperExpr::NOT); delete LOC;}

%type lValue {AST::LValue*}
%destructor lValue {delete $$;}
lValue(A) ::= IDENTIFIER(B) . {A = new AST::VarLValue(B->loc, B->str); delete B;}
lValue(A) ::= expr(B) DOT(LOC) IDENTIFIER(C) . {A = new AST::VarLValue(LOC->loc, B, C->str); delete LOC;}

%type exprList {AST::ExprList*}
%destructor exprList {delete $$;}
exprList(A) ::= . {A = new AST::ExprList();}
exprList(A) ::= exprListH(B) . {A = B;}
%type exprListH {AST::ExprList*}
%destructor exprListH {delete $$;}
exprListH(A) ::= expr(B) . {A = new AST::ExprList(B);}
exprListH(A) ::= exprListH(B) CMA expr(C) . {A = new AST::ExprList(B, C);}

%type lValueList {AST::LValueList*}
%destructor lValueList {delete $$;}
lValueList(A) ::= . {A = new AST::LValueList();}
lValueList(A) ::= lValueListH(B) . {A = B;}
%type lValueListH {AST::LValueList*}
%destructor lValueListH {delete $$;}
lValueListH(A) ::= lValue(B) . {A = new AST::LValueList(B);}
lValueListH(A) ::= lValueListH(B) CMA lValue(C) . {A = new AST::LValueList(B, C);}

%type iDList {AST::IDList*}
%destructor iDList {delete $$;}
iDList(A) ::= . {A = new AST::IDList();}
iDList(A) ::= iDListH(B) . {A = B;}
%type iDListH {AST::IDList*}
%destructor iDListH {delete $$;}
iDListH(A) ::= IDENTIFIER(B) . {A = new AST::IDList(B->str);}
iDListH(A) ::= iDListH(B) CMA IDENTIFIER(C) . {A = new AST::IDList(B, C->str);}
