#include "AST/DoubleOperExpr.h"
#include "AST/Visitor.h"

namespace AST {
    void DoubleOperExpr::visit(Visitor* that) {
        that->visitDoubleOperExpr(this);
    }
}
