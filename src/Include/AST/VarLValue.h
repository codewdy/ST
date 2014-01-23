#ifndef ST_8271892302_AST_VARLVALUE
#define ST_8271892302_AST_VARLVALUE
#include "LValue.h"
#include <string>
#include "LocaleExpr.h"
namespace AST {
    class Expr;
    /**AST for obj\.attr Expr.*/
    class VarLValue : public LValue {
    public:
        Expr *obj;///<obj in obj\.attr.
        std::string attr;///<attr in obj\.attr.
        VarLValue(Location _loc, std::string _attr) : LValue(_loc), obj(new LocaleExpr(_loc)), attr(_attr) {}
        VarLValue(Location _loc, Expr* _obj, std::string _attr) : LValue(_loc), obj(_obj), attr(_attr) {}
        void visit(Visitor* that);
        ~VarLValue();
    };
}
#endif

