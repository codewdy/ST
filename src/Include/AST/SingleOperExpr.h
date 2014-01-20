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
        Expr *expr1;
        enum Oper {
            NEG, NOT
        } op;
        static SingleOperExpr* Create(Expr* _expr1, Oper _op);
        void visit(Visitor* that);
    };
}
#endif
