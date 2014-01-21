#ifndef ST_8327192384_AST_CALLEXPR
#define ST_8327192384_AST_CALLEXPR
#include "Expr.h"
namespace AST
{
    class ExprList;
    class CallExpr : public Expr
    {
    protected:
        CallExpr();
    public:
        Expr* func;
        std::vector<Expr*> parms;
        static CallExpr* Create(Expr* _func, ExprList* _parms);
        void visit (Visitor* that);
    };
}
#endif

