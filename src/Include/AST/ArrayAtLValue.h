#ifndef ST_7328743281_AST_ARRAYATLVALUE
#define ST_7328743281_AST_ARRAYATLVALUE
#include "LValue.h"
namespace AST
{
    class Expr;
    class Oper;
    class ArrayAtLValue : public LValue
    {
    protected:
        ArrayAtLValue();
        ArrayAtLValue(const ArrayAtLValue&);
    public:
        static ArrayAtLValue* Create(Expr* s1, Oper* s2, Expr* s3, Oper* s4);
    };
}
#endif

