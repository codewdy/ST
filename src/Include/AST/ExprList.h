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
        static void FillVector(ExprList* src, std::vector<Expr*>& dst) {src->exprs.swap(dst); delete src;}
        std::vector<Expr*> exprs;
        ExprList(Location _loc) : AST(_loc) {}
        ExprList(Location _loc, Expr* s1) : AST(_loc), exprs(1, s1) {}
        ExprList(Location _loc, ExprList* left, Expr* right) : AST(_loc) {FillVector(left, exprs); exprs.push_back(right);}
    };
}
#endif
