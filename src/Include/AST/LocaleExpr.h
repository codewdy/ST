#ifndef ST_47297234932_AST_LOCALEEXPR
#define ST_47297234932_AST_LOCALEEXPR
#include "Expr.h"
namespace AST
{
    class LocaleExpr : public Expr
    {
    protected:
        LocaleExpr();
        LocaleExpr(const LocaleExpr&);
    public:
        static LocaleExpr* Create();
    };
}
#endif

