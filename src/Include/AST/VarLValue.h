#ifndef ST_8271892302_AST_VARLVALUE
#define ST_8271892302_AST_VARLVALUE
#include "LValue.h"
#include <string>
namespace AST
{
    class Expr;
    class VarLValue : public LValue {
    protected:
        VarLValue();
        VarLValue(const VarLValue&);
    public:
        Expr *obj;
        std::string *attr;
        static VarLValue* Create(std::string _attr);
        static VarLValue* Create(Expr* _obj, std::string _attr);
        void visit(Visitor* that);
    };
}
#endif

