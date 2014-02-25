#ifndef ST_47297234932_AST_LOCALEEXPR
#define ST_47297234932_AST_LOCALEEXPR
#include "Expr.h"
namespace AST
{
    /**AST for the Locale.*/
    class LocaleExpr : public Expr
    {
    public:
        LocaleExpr(Location _loc) : Expr(_loc) {}
        void visit(Visitor* that);
    };
}
#endif

