#ifndef ST_9023842910_AST_LISTEXPR
#define ST_9023842910_AST_LISTEXPR
#include "Expr.h"
#include <vector>
#include "XList.h"
namespace AST {
    /**AST for the List Expr.*/
    class ListExpr : public Expr {
    public:
        std::vector<Expr*> exprs;///<List of Element.
        ListExpr(Location _loc, ExprList* _exprs) : Expr(_loc) {ExprList::FillVector(_exprs, exprs);}
        void visit(Visitor* that);
        ~ListExpr();
    };
}
#endif

