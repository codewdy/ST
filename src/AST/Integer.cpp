#include "AST/Integer.h"
#include "AST/Visitor.h"

namespace AST {
    Integer::Integer(Location _loc, const char* _str) : Expr(_loc), str(_str) {}
    void Integer::visit(Visitor* v) {
        v->visitInteger(this);
    }
}

