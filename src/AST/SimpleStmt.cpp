#include "AST/SimpleStmt.h"
#include "AST/Visitor.h"

namespace AST {
    void SimpleStmt::visit(Visitor* v) {
        v->visitSimpleStmt(this);
    }
}

