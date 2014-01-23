#ifndef ST_2933102910_AST_FORSTMT
#define ST_2933102910_AST_FORSTMT
#include "Stmt.h"
namespace AST
{
    class LValue;
    class Expr;
    class Stmt;
    /**AST for For Statement(a loop get all element from a set).*/
    class ForStmt : public Stmt {
    public:
        LValue* var;///<the element.
        Expr* set;///<the set contains element.
        Stmt* loop;///<the code for every element.
        ForStmt(Location _loc, LValue* _var, Expr* _set, Stmt* _loop) : Stmt(_loc), var(_var), set(_set), loop(_loop) {}
        void visit(Visitor* that);
        ~ForStmt();
    };
}
#endif
