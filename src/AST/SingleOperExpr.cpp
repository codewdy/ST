#include "AST/SingleOperExpr.h"
#include "AST/Visitor.h"

namespace AST {
    void SingleOperExpr::visit(Visitor* that) {
        that->visitSingleOperExpr(this);
    }
}
