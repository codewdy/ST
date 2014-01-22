#ifndef ST_2933102910_AST_FORSTMT
#define ST_2933102910_AST_FORSTMT
#include "Stmt.h"
namespace AST
{
    class LValue;
    class Expr;
    class Stmt;
    class ForStmt : public Stmt {
    protected:
        ForStmt(const ForStmt&);
    public:
        LValue* var;
        Expr* set;
        Stmt* loop;
        ForStmt(Location _loc, LValue* _var, Expr* _set, Stmt* _loop) : Stmt(_loc), var(_var), set(_set), loop(_loop) {}
        void visit(Visitor* that);
    };
}
#endif
