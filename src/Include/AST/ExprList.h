#ifndef ST_1857664392_AST_EXPRLIST
#define ST_1857664392_AST_EXPRLIST
#include "AST.h"
namespace AST
{
    class Expr;
    class Oper;
    class ExprList : public AST
    {
    protected:
        ExprList();
        ExprList(const ExprList&);
    public:
        static ExprList* Create();
        static ExprList* Create(Expr* s1);
        static ExprList* Create(ExprList* s1, Oper* s2, Expr* s3);
    };
}
#endif
