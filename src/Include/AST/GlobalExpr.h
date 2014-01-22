#ifndef ST_82371923842_AST_GLOBALEXPR
#define ST_82371923842_AST_GLOBALEXPR
#include "Expr.h"
namespace AST
{
    class GlobalExpr : public Expr
    {
    protected:
        GlobalExpr(const GlobalExpr&);
    public:
        GlobalExpr(Location _loc) : Expr(_loc) {}
    };
}
#endif

