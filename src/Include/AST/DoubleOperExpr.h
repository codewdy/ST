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
        Expr *expr1, *expr2;
        enum Oper {
            PLUS, MINUS, MUL, DIV, MOD, GT, LT, GE, LE, EQ, NE, AND, OR
        } oper;
        static DoubleOperExpr* Create(Expr* _expr1, Expr* _expr2, Oper _op);
        void visit(Visitor* that);
    };
}
#endif

