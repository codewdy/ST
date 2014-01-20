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
}
