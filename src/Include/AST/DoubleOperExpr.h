#ifndef ST_1021907482_AST_DOUBLEOPEREXPR
#define ST_1021907482_AST_DOUBLEOPEREXPR
#include "Expr.h"
namespace AST
{
    class DoubleOperExpr : public Expr {
    protected:
        DoubleOperExpr();
    public:
        Expr *expr1, *expr2;
        enum Oper {
            PLUS, MINUS, MUL, DIV, MOD, GT, LT, GE, LE, EQ, NE, AND, OR
        } oper;
        DoubleOperExpr(Location _loc, Expr* _expr1, Expr* _expr2, Oper _oper) : Expr(_loc), expr1(_expr1), expr2(_expr2), oper(_oper) {}
        void visit(Visitor* that);
    };
}
#endif

