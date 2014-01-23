#ifndef ST_9382741231_AST_EXPR
#define ST_9382741231_AST_EXPR
#include "AST.h"
namespace AST
{
    /**AST for virtual Expr.*/
    class Expr : public AST
    {
    public:
        Expr(Location _loc) : AST(_loc) {}
    };
}
#endif

