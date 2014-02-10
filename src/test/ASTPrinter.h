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
    ST_DEF_VISIT_AST_CLASS(Program)
    ST_DEF_VISIT_AST_CLASS(SimpleStmt)
    ST_DEF_VISIT_AST_CLASS(ForStmt)
    ST_DEF_VISIT_AST_CLASS(WhileStmt)
    ST_DEF_VISIT_AST_CLASS(IfStmt)
    ST_DEF_VISIT_AST_CLASS(StmtBlock)
    ST_DEF_VISIT_AST_CLASS(BreakStmt)
    ST_DEF_VISIT_AST_CLASS(ReturnStmt)
    ST_DEF_VISIT_AST_CLASS(ListExpr)
    ST_DEF_VISIT_AST_CLASS(CallExpr)
    ST_DEF_VISIT_AST_CLASS(FuncDef)
    ST_DEF_VISIT_AST_CLASS(StateDef)
    ST_DEF_VISIT_AST_CLASS(GlobalExpr)
    ST_DEF_VISIT_AST_CLASS(LocaleExpr)
    ST_DEF_VISIT_AST_CLASS(NullExpr)
    ST_DEF_VISIT_AST_CLASS(DoubleOperExpr)
    ST_DEF_VISIT_AST_CLASS(SingleOperExpr)
    ST_DEF_VISIT_AST_CLASS(ArrayAtLValue)
    ST_DEF_VISIT_AST_CLASS(VarLValue)
    ST_DEF_VISIT_AST_CLASS(Double)
    ST_DEF_VISIT_AST_CLASS(Integer)
    ST_DEF_VISIT_AST_CLASS(String)
};
#endif

