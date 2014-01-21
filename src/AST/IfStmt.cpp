#include "AST/IfStmt.h"
#include "AST/Visitor.h"

namespace AST {
    void IfStmt::visit(Visitor* that) {
        that->visitIfStmt(this);
    }
}
