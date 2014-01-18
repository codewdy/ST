#ifndef ST_9023842910_AST_LISTEXPR
#define ST_9023842910_AST_LISTEXPR
#include "Expr.h"
namespace AST
{
    class ExprList;
    class Oper;
    class ListExpr : public AST
    {
    protected:
        ListExpr();
        ListExpr(const ListExpr&);
    public:
        static ListExpr* Create(Oper* s1, ExprList* s2, Oper* s3);
    };
}
#endif

