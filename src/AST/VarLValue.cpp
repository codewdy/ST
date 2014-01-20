#include "AST/VarLValue.h"
#include "AST/Visitor.h"

namespace AST {
    void VarLValue::visit(Visitor* that) {
        that->visitVarLValue(this);
    }
}
