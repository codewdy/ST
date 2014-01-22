#ifndef ST_8327192384_AST_CALLEXPR
#define ST_8327192384_AST_CALLEXPR
#include "Expr.h"
#include "XList.h"
namespace AST
{
    class CallExpr : public Expr
    {
    public:
        Expr* func;
        std::vector<Expr*> parms;
        CallExpr(Location _loc, Expr* _func, ExprList* _parms) : Expr(_loc), func(_func) {ExprList::FillVector(_parms, parms);}
        void visit (Visitor* that);
    };
}
#endif

