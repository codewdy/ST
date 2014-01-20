#include "AST/ArrayAtLValue.h"
#include "AST/Visitor.h"

namespace AST {
    void ArrayAtLValue::visit(Visitor* that) {
        that->visitArrayAtLValue(this);
    }
}
