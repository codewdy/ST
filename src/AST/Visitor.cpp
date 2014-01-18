#include "AST/ALL.h"
namespace AST
{
    void Visitor::visit(AST* that)
    {
        return that->visit(this);
    }

    void Visitor::visitInteger(Integer* that) {
    }

    void Visitor::visitDouble(Double* that) {

    }
}
