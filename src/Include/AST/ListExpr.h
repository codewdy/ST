#ifndef ST_9023842910_AST_LISTEXPR
#define ST_9023842910_AST_LISTEXPR
#include "Expr.h"
#include <vector>
namespace AST
{
    class ExprList;
    class ListExpr : public Expr
    {
    protected:
        ListExpr();
        ListExpr(const ListExpr&);
    public:
        std::vector<Expr*> exprs;
        static ListExpr* Create(ExprList* _exprs);
        void visit(Visitor* that);
    };
}
#endif

