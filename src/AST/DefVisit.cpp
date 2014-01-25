#include "AST/ALL.h"

namespace AST {
#define DefClassVisit(CLASS) void CLASS::visit(Visitor* that) {that->visit##CLASS(this);}
    DefClassVisit(Integer)
    DefClassVisit(Double)
    DefClassVisit(String)
    DefClassVisit(Program)
    DefClassVisit(SimpleStmt)
    DefClassVisit(ForStmt)
    DefClassVisit(WhileStmt)
    DefClassVisit(IfStmt)
    DefClassVisit(StmtBlock)
    DefClassVisit(BreakStmt)
    DefClassVisit(ReturnStmt)
    DefClassVisit(ListExpr)
    DefClassVisit(CallExpr)
    DefClassVisit(FuncDef)
    DefClassVisit(StateDef)
    DefClassVisit(GlobalExpr)
    DefClassVisit(LocaleExpr)
    DefClassVisit(NullExpr)
    DefClassVisit(DoubleOperExpr)
    DefClassVisit(SingleOperExpr)
    DefClassVisit(VarLValue)
    DefClassVisit(ArrayAtLValue)
}
