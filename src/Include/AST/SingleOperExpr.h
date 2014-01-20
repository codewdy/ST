#ifndef ST_3291283292_AST_SINGLEOPEREXPR
#define ST_3291283292_AST_SINGLEOPEREXPR
#include "Expr.h"
namespace AST
{
    class SingleOperExpr : public Expr {
    protected:
        SingleOperExpr();
        SingleOperExpr(const SingleOperExpr&);
    public:
        enum Oper {
            NEG, NOT
        } op;
        static SingleOperExpr* Create(Expr* _e, Oper _op);
    };
}
#endif
