#ifndef ST_1857664392_AST_EXPRLIST
#define ST_1857664392_AST_EXPRLIST
#include "AST.h"
#include <vector>
namespace AST
{
    class Expr;
    class ExprList : public AST
    {
    protected:
        ExprList();
        ExprList(const ExprList&);
    public:
        std::vector<Expr*> exprs;
        static ExprList* Create();
        static ExprList* Create(Expr* s1);
        static ExprList* Create(ExprList* left, Expr* right);
        static void FillVector(ExprList* src, std::vector<Expr*>& dst);
    };
}
#endif
