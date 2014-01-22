#ifndef ST_9023842910_AST_LISTEXPR
#define ST_9023842910_AST_LISTEXPR
#include "Expr.h"
#include <vector>
#include "XList.h"
namespace AST
{
    class ListExpr : public Expr
    {
    public:
        std::vector<Expr*> exprs;
        ListExpr(Location _loc, ExprList* _exprs) : Expr(_loc) {ExprList::FillVector(_exprs, exprs);}
        void visit(Visitor* that);
    };
}
#endif

