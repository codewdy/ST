#include "AST/CallExpr.h"
#include "AST/Visitor.h"

namespace AST {
    void CallExpr::visit(Visitor* that) {
        that->visitCallExpr(this);
    }
}
