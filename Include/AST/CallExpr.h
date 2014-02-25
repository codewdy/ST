#ifndef ST_8327192384_AST_CALLEXPR
#define ST_8327192384_AST_CALLEXPR
#include "Expr.h"
#include "XList.h"
namespace AST
{
    /**AST for calling a function.*/
    class CallExpr : public Expr
    {
    public:
        Expr* func;///<Function value.
        std::vector<Expr*> parms;///<Function Call Parms.
        CallExpr(Location _loc, Expr* _func, ExprList* _parms) : Expr(_loc), func(_func) {ExprList::FillVector(_parms, parms);}
        void visit (Visitor* that);
        ~CallExpr();
    };
}
#endif

