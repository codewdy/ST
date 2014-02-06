#ifndef ST_9732812389_TEST_PARSER_ASTPRINTER
#define ST_9732812389_TEST_PARSER_ASTPRINTER
#include "AST/ALL.h"
#include <string>
#include <iostream>

class ASTPrinter : public AST::Visitor {
    std::string prefix;
    std::ostream& fout;
public:
    ASTPrinter(std::ostream& _fout) : prefix(""), fout(_fout) {} 
    DefVisitASTClass(Program)
    DefVisitASTClass(SimpleStmt)
    DefVisitASTClass(ForStmt)
    DefVisitASTClass(WhileStmt)
    DefVisitASTClass(IfStmt)
    DefVisitASTClass(StmtBlock)
    DefVisitASTClass(BreakStmt)
    DefVisitASTClass(ReturnStmt)
    DefVisitASTClass(ListExpr)
    DefVisitASTClass(CallExpr)
    DefVisitASTClass(FuncDef)
    DefVisitASTClass(StateDef)
    DefVisitASTClass(GlobalExpr)
    DefVisitASTClass(LocaleExpr)
    DefVisitASTClass(NullExpr)
    DefVisitASTClass(DoubleOperExpr)
    DefVisitASTClass(SingleOperExpr)
    DefVisitASTClass(ArrayAtLValue)
    DefVisitASTClass(VarLValue)
    DefVisitASTClass(Double)
    DefVisitASTClass(Integer)
    DefVisitASTClass(String)
};
#endif

