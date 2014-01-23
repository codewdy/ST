#ifndef ST_3291283292_AST_SINGLEOPEREXPR
#define ST_3291283292_AST_SINGLEOPEREXPR
#include "Expr.h"
namespace AST
{
    /**AST for Single Operator Expr.*/
    class SingleOperExpr : public Expr {
    public:
        Expr *expr1;///<Opcode.
        enum Oper {
            NEG, NOT
        } oper;///<Oper Type.
        SingleOperExpr(Location _loc, Expr* _expr1, Oper _oper) : Expr(_loc), expr1(_expr1), oper(_oper) {}
        void visit(Visitor* that);
        ~SingleOperExpr();
    };
}
#endif
