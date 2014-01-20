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
        Expr *array, *index;
        static ArrayAtLValue* Create(Expr* _array, Expr* _index);
        void visit(Visitor* that);
    };
}
#endif

