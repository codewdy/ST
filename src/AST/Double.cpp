#include "AST/Double.h"
#include "AST/Visitor.h"

namespace AST
{
    Double::Double(Location _loc, const char* _str) : Expr(_loc), str(_str) {}
    void Double::visit(Visitor* v) {
        return v->visitDouble(this);
    }
}
