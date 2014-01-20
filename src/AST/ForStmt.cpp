#include "AST/ForStmt.h"
#include "AST/Visitor.h"
namespace AST {
    void ForStmt::visit(Visitor* that) {
        that->visitForStmt(this);
    }
}
