#ifndef ST_7382198328_AST_LVALUE
#define ST_7382198328_AST_LVALUE
#include "Expr.h"
namespace AST
{
    class LValue : public Expr
    {
    public:
        LValue(Location _loc) : Expr(_loc) {}
    };
}
#endif

