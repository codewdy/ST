#ifndef ST_12938714938_AST_NULLEXPR
#define ST_12938714938_AST_NULLEXPR
#include "Expr.h"
namespace AST {
    /**AST for the Null.*/
    class NullExpr : public Expr {
    public:
        NullExpr(Location _loc) : Expr(_loc) {}
        void visit(Visitor* that);
    };
}
#endif

