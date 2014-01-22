#include "AST/Integer.h"
#include "AST/Visitor.h"

namespace AST {
    void Integer::visit(Visitor* v) {
        v->visitInteger(this);
    }
}

