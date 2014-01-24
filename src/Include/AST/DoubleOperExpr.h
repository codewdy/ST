#ifndef ST_1021907482_AST_DOUBLEOPEREXPR
#define ST_1021907482_AST_DOUBLEOPEREXPR
#include "Expr.h"
namespace AST
{
    /**AST for Expr with Binary Operator*/
    class DoubleOperExpr : public Expr {
    public:
        Expr *expr1;///<Left Opcode.
        Expr *expr2;///<Right Opcode.
        enum Oper {
            PLUS, MINUS, MUL, DIV, MOD, GT, LT, GE, LE, EQ, NE, AND, OR, ASG
        } oper;///<Operator type.
        DoubleOperExpr(Location _loc, Expr* _expr1, Expr* _expr2, Oper _oper) : Expr(_loc), expr1(_expr1), expr2(_expr2), oper(_oper) {}
        void visit(Visitor* that);
        ~DoubleOperExpr();
    };
}
#endif

