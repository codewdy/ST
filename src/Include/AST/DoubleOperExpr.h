#ifndef ST_1021907482_AST_DOUBLEOPEREXPR
#define ST_1021907482_AST_DOUBLEOPEREXPR
#include "Expr.h"
namespace AST
{
    class Oper;
    class DoubleOperExpr : public Expr {
    protected:
        DoubleOperExpr();
        DoubleOperExpr(const DoubleOperExpr&);
    public:
        static DoubleOperExpr* Create(Expr* s1, Oper* s2, Expr* s3);
    };
}
#endif

