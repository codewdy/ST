#ifndef ST_1021907482_AST_DOUBLEOPEREXPR
#define ST_1021907482_AST_DOUBLEOPEREXPR
#include "Expr.h"
namespace AST
{
    class DoubleOperExpr : public Expr {
    protected:
        DoubleOperExpr();
        DoubleOperExpr(const DoubleOperExpr&);
    public:
        enum Oper {
            PLUS, MINUS, MUL, DIV, MOD, GT, LT, GE, LE, EQ, NE, AND, OR
        } op;
        static DoubleOperExpr* Create(Expr* _e1, Expr* _e2, Oper _op);
    };
}
#endif

