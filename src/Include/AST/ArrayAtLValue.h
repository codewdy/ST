#ifndef ST_7328743281_AST_ARRAYATLVALUE
#define ST_7328743281_AST_ARRAYATLVALUE
#include "LValue.h"
namespace AST
{
    class Expr;
    class ArrayAtLValue : public LValue
    {
    public:
        Expr *array, *index;
        ArrayAtLValue(Location _loc, Expr* _array, Expr* _index) : LValue(_loc), array(_array), index(_index) {}
        void visit(Visitor* that);
    };
}
#endif

