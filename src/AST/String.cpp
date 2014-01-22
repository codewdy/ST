#include "AST/String.h"
#include "AST/Visitor.h"

namespace AST
{
    void String::visit(Visitor* v) {
        v->visitString(this);
    }
}

