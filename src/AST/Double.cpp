#include "AST/Double.h"
#include "AST/Visitor.h"

namespace AST
{
    void Double::visit(Visitor* v) {
        return v->visitDouble(this);
    }
}
