#include "AST/ALL.h"
namespace AST
{
    void Visitor::visit(AST* that) {
        return that->visit(this);
    }

    void Visitor::visitInteger(Integer* that) {
    }

    void Visitor::visitDouble(Double* that) {
    }

    void Visitor::visitString(String* that) {
    }

    void Visitor::visitProgram(Program* that) {
        for (auto stmt : that->stmts)
            stmt->visit(this);
    }

    void Visitor::visitSimpleStmt(SimpleStmt* that) {
        that->expr->visit(this);
    }

    void Visitor::visitForStmt(ForStmt* that) {
        that->var->visit(this);
        that->set->visit(this);
        that->loop->visit(this);
    }

    void Visitor::visitWhileStmt(WhileStmt* that) {
        that->condition->visit(this);
        that->loop->visit(this);
    }

    void Visitor::visitIfStmt(IfStmt* that) {
        that->condition->visit(this);
        that->yes->visit(this);
        if (that->no)
            that->no->visit(this);
    }

    void Visitor::visitStmtBlock(StmtBlock* that) {
        for (auto stmt : that->stmts)
            stmt->visit(this);
    }

    void Visitor::visitBreakStmt(BreakStmt* that) {
    }
    
    void Visitor::visitReturnStmt(ReturnStmt* that) {
        if (that->expr)
            that->expr->visit(this);
    }

    void Visitor::visitListExpr(ListExpr* that) {
        for (auto expr : that->exprs)
            expr->visit(this);
    }

    void Visitor::visitCallExpr(CallExpr* that) {
        that->func->visit(this);
        for (auto parm : that->parms)
            parm->visit(this);
    }

    void Visitor::visitFuncDef(FuncDef* that) {
        that->stmts->visit(this);
    }

    void Visitor::visitStateDef(StateDef* that) {
        that->stmts->visit(this);
    }

    void Visitor::visitGlobalExpr(GlobalExpr* that) {
    }

    void Visitor::visitLocaleExpr(LocaleExpr* that) {
    }

    void Visitor::visitNullExpr(NullExpr* that) {
    }

    void Visitor::visitDoubleOperExpr(DoubleOperExpr* that) {
        that->expr1->visit(this);
        that->expr2->visit(this);
    }

    void Visitor::visitSingleOperExpr(SingleOperExpr* that) {
        that->expr1->visit(this);
    }

    void Visitor::visitVarLValue(VarLValue* that) {
        that->obj->visit(this);
    }

    void Visitor::visitArrayAtLValue(ArrayAtLValue* that) {
        that->array->visit(this);
        that->index->visit(this);
    }

    Visitor::~Visitor() {
    }
}
