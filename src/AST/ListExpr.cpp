#include "AST/ListExpr.h"
#include "AST/Visitor.h"

namespace AST {
    void ListExpr::visit(Visitor* that) {
        that->visitListExpr(this);
    }
}
