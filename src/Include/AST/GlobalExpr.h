#ifndef ST_82371923842_AST_GLOBALEXPR
#define ST_82371923842_AST_GLOBALEXPR
#include "Expr.h"
namespace AST {
    /**AST for the Global.*/
    class GlobalExpr : public Expr {
    public:
        GlobalExpr(Location _loc) : Expr(_loc) {}
        void visit(Visitor* that);
    };
}
#endif

