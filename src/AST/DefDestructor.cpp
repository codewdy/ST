#include "AST/ALL.h"

namespace AST {
    AST::~AST() {
    }
    
    Program::~Program() {
        for (auto stmt : stmts)
            delete stmt;
    }

    SimpleStmt::~SimpleStmt() {
        delete expr;
    }

    ForStmt::~ForStmt() {
        delete var;
        delete set;
        delete loop;
    }
    
    WhileStmt::~WhileStmt() {
        delete condition;
        delete loop;
    }

    IfStmt::~IfStmt() {
        delete condition;
        delete yes;
        delete no;
    }

    StmtBlock::~StmtBlock() {
        for (auto stmt : stmts)
            delete stmt;
    }
    
    ReturnStmt::~ReturnStmt() {
        delete expr;
    }

    ListExpr::~ListExpr() {
        for (auto expr : exprs)
            delete expr;
    }

    CallExpr::~CallExpr() {
        delete func;
        for (auto parm : parms)
            delete parm;
    }

    FuncDef::~FuncDef() {
        delete stmts;
    }

    StateDef::~StateDef() {
        delete stmts;
        delete base;
    }

    DoubleOperExpr::~DoubleOperExpr() {
        delete expr1;
        delete expr2;
    }

    SingleOperExpr::~SingleOperExpr() {
        delete expr1;
    }

    VarLValue::~VarLValue() {
        delete obj;
    }

    ArrayAtLValue::~ArrayAtLValue() {
        delete array;
        delete index;
    }
}
