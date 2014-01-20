#include "AST/ALL.h"
namespace AST
{
    void Visitor::visit(AST* that) {
        return that->visit(this);
    }

    void Visitor::visitIdentifier(Identifier* that) {
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

    void Visitor::visitStmtBlock(StmtBlock* that) {
        for (auto stmt : that->stmts)
            stmt->visit(this);
    }

    void Visitor::visitListExpr(ListExpr* that) {
        for (auto expr : that->exprs)
            expr->visit(this);
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
}
