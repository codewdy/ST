#include "AST/WhileStmt.h"
#include "AST/Visitor.h"

namespace AST {
    void WhileStmt::visit(Visitor* that) {
        that->visitWhileStmt(this);
    }
}
