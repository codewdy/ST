#include "AST/ALL.h"

namespace AST {
#define ST_DEF_CLASS_VISIT(CLASS) void CLASS::visit(Visitor* that) {that->visit##CLASS(this);}
    ST_DEF_CLASS_VISIT(Integer)
    ST_DEF_CLASS_VISIT(Double)
    ST_DEF_CLASS_VISIT(String)
    ST_DEF_CLASS_VISIT(Program)
    ST_DEF_CLASS_VISIT(SimpleStmt)
    ST_DEF_CLASS_VISIT(ForStmt)
    ST_DEF_CLASS_VISIT(WhileStmt)
    ST_DEF_CLASS_VISIT(IfStmt)
    ST_DEF_CLASS_VISIT(StmtBlock)
    ST_DEF_CLASS_VISIT(BreakStmt)
    ST_DEF_CLASS_VISIT(ReturnStmt)
    ST_DEF_CLASS_VISIT(ListExpr)
    ST_DEF_CLASS_VISIT(CallExpr)
    ST_DEF_CLASS_VISIT(FuncDef)
    ST_DEF_CLASS_VISIT(StateDef)
    ST_DEF_CLASS_VISIT(GlobalExpr)
    ST_DEF_CLASS_VISIT(LocaleExpr)
    ST_DEF_CLASS_VISIT(NullExpr)
    ST_DEF_CLASS_VISIT(DoubleOperExpr)
    ST_DEF_CLASS_VISIT(SingleOperExpr)
    ST_DEF_CLASS_VISIT(VarLValue)
    ST_DEF_CLASS_VISIT(ArrayAtLValue)
}
