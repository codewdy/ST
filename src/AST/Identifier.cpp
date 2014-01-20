#include "AST/Identifier.h"
#include "AST/Visitor.h"

namespace AST {
    void Identifier::visit(Visitor* that) {
        that->visitIdentifier(this);
    }
}
