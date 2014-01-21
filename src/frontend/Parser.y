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
#include "Exception/Exception.h"
#include "Lexer.h"
AST::Program* GetProgram(std::string filename) {
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
        return ret;
    } catch (Exception::Exception e) {
        delete fn;
        ParseFree(parser, free);
        throw e;
    }
}
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
//hack Lexer.l
%nonassoc BREAK .

%start_symbol program

%token_type {Lex*}
%token_destructor {delete $$;}

%type program {AST::Program*}
program(A) ::= stmtList(B). {*ret = A = AST::Program::Create(B);}

%type stmtList {AST::StmtList*}
%destructor stmtList {delete $$;}
stmtList(A) ::= . {A = AST::StmtList::Create();}
stmtList(A) ::= stmtList(B) stmt(C). {A = AST::StmtList::Create(B, C);}

%type stmt {AST::Stmt*}
%destructor stmt {delete $$;}
stmt(A) ::= expr(B) SEM. {A = AST::SimpleStmt::Create(B);}
stmt(A) ::= FOR LLC lValue(B) COL expr(C) RLC stmt(D). {A = AST::ForStmt::Create(B, C, D);}
stmt(A) ::= WHILE LLC expr(B) RLC stmt(C) . {A = AST::WhileStmt::Create(B, C);}
stmt(A) ::= IF LLC expr(B) RLC stmt(C) . {A = AST::IfStmt::Create(B, C);}
stmt(A) ::= IF LLC expr(B) RLC stmt(C) ELSE stmt(D) . {A = AST::IfStmt::Create(B, C, D);}
stmt(A) ::= stmtBlock(B) . {A = B;}

%type stmtBlock {AST::StmtBlock*}
%destructor stmtBlock {delete $$;}
stmtBlock(A) ::= LGC stmtList(B) RGC . {A = AST::StmtBlock::Create(B);}

%type expr {AST::Expr*}
%destructor expr {delete $$;}
//Literal Expr
expr(A) ::= STRING(B) . {A = new AST::String(B->loc, B->str); delete B;}
expr(A) ::= INTEGER(B) . {A = new AST::Integer(B->loc, B->str); delete B;}
expr(A) ::= DOUBLE(B) . {A = new AST::Double(B->loc, B->str); delete B;}
//LValue Expr
expr(A) ::= lValue(B) . {A = B;}
//Call Expr
expr(A) ::= expr(B) LLC exprList(C) RLC . {A = AST::CallExpr::Create(B, C);}
//Func Def Expr
expr(A) ::= FUNC lValueList(B) LLC iDList(C) RLC stmtBlock(D) . {A = AST::FuncDef::Create(B, C, D);}
//State Def Expr
expr(A) ::= STATE lValueList(B) stmtBlock(C) . {A = AST::StateDef::Create(B, C);}
//List Expr
expr(A) ::= LMC exprList(B) RLC . {A = AST::ListExpr::Create(B);}
//Simple Expr
expr(A) ::= LLC expr(B) RLC . {A = B;}
expr(A) ::= expr(B) PLUS expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::PLUS);}
expr(A) ::= expr(B) MINUS expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::MINUS);}
expr(A) ::= expr(B) MUL expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::MUL);}
expr(A) ::= expr(B) DIV expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::DIV);}
expr(A) ::= expr(B) MOD expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::MOD);}
expr(A) ::= expr(B) LT expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::LT);}
expr(A) ::= expr(B) GT expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::GT);}
expr(A) ::= expr(B) LE expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::LE);}
expr(A) ::= expr(B) GE expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::GE);}
expr(A) ::= expr(B) EQ expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::EQ);}
expr(A) ::= expr(B) NE expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::NE);}
expr(A) ::= expr(B) AND expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::AND);}
expr(A) ::= expr(B) OR expr(C) . {A = AST::DoubleOperExpr::Create(B, C, AST::DoubleOperExpr::OR);}
expr(A) ::= MINUS expr(B) . [NEG] {A = AST::SingleOperExpr::Create(B, AST::SingleOperExpr::NEG);}
expr(A) ::= NOT expr(B) . [NEG] {A = AST::SingleOperExpr::Create(B, AST::SingleOperExpr::NOT);}

%type lValue {AST::LValue*}
%destructor lValue {delete $$;}
lValue(A) ::= IDENTIFIER(B) . {A = AST::VarLValue::Create(B->str);}
lValue(A) ::= expr(B) DOT IDENTIFIER(C) . {A = AST::VarLValue::Create(B, C->str);}

%type exprList {AST::ExprList*}
%destructor exprList {delete $$;}
exprList(A) ::= . {A = AST::ExprList::Create();}
exprList(A) ::= exprListH(B) . {A = B;}
%type exprListH {AST::ExprList*}
%destructor exprListH {delete $$;}
exprListH(A) ::= expr(B) . {A = AST::ExprList::Create(B);}
exprListH(A) ::= exprListH(B) CMA expr(C) . {A = AST::ExprList::Create(B, C);}

%type lValueList {AST::LValueList*}
%destructor lValueList {delete $$;}
lValueList(A) ::= . {A = AST::LValueList::Create();}
lValueList(A) ::= lValueListH(B) . {A = B;}
%type lValueListH {AST::LValueList*}
%destructor lValueListH {delete $$;}
lValueListH(A) ::= lValue(B) . {A = AST::LValueList::Create(B);}
lValueListH(A) ::= lValueListH(B) CMA lValue(C) . {A = AST::LValueList::Create(B, C);}

%type iDList {AST::IDList*}
%destructor iDList {delete $$;}
iDList(A) ::= . {A = AST::IDList::Create();}
iDList(A) ::= iDListH(B) . {A = B;}
%type iDListH {AST::IDList*}
%destructor iDListH {delete $$;}
iDListH(A) ::= IDENTIFIER(B) . {A = AST::IDList::Create(B->str);}
iDListH(A) ::= iDListH(B) CMA IDENTIFIER(C) . {A = AST::IDList::Create(B, C->str);}
