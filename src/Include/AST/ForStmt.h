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
        ForStmt();
        ForStmt(const ForStmt&);
    public:
        LValue* var;
        Expr* set;
        Stmt* loop;
        static ForStmt* Create(LValue* _var, Expr* _set, Stmt* _loop);
        void visit(Visitor* that);
    };
}
#endif
