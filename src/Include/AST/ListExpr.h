#ifndef ST_9023842910_AST_LISTEXPR
#define ST_9023842910_AST_LISTEXPR
#include "Expr.h"
#include <vector>
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
        std::vector<Expr*> exprs;
        static ListExpr* Create(Oper* s1, ExprList* s2, Oper* s3);
        void visit(Visitor* that);
    };
}
#endif

