#ifndef ST_7328743281_AST_ARRAYATLVALUE
#define ST_7328743281_AST_ARRAYATLVALUE
#include "LValue.h"
namespace AST
{
    class Expr;
    /**Get a element from a container.*/
    class ArrayAtLValue : public LValue
    {
    public:
        Expr *array;///<Array in "Array[Index]".
        Expr *index;///<Index in "Array[Index]".
        ArrayAtLValue(Location _loc, Expr* _array, Expr* _index) : LValue(_loc), array(_array), index(_index) {}
        void visit(Visitor* that);
        virtual ~ArrayAtLValue();
    };
}
#endif

