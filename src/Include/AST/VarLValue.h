#ifndef ST_8271892302_AST_VARLVALUE
#define ST_8271892302_AST_VARLVALUE
#include "LValue.h"
namespace AST
{
    class Identifier;
    class Expr;
    class Oper;
    class VarLValue : public LValue {
    protected:
        VarLValue();
        VarLValue(const VarLValue&);
    public:
        Expr *obj;
        Identifier *attr;
        static VarLValue* Create(Identifier* s1);
        static VarLValue* Create(Expr* _obj, Identifier* _attr);
        void visit(Visitor* that);
    };
}
#endif

