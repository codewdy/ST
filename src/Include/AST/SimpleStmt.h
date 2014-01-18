#ifndef ST_5391073821_AST_SIMPLESTMT
#define ST_5391073821_AST_SIMPLESTMT
#include "Stmt.h"
namespace AST
{
    class Expr;
    class Oper;
    class SimpleStmt : public Stmt
    {
    protected:
        SimpleStmt();
        SimpleStmt(const SimpleStmt&);
    public:
        static SimpleStmt* Create(Expr* s1, Oper* s2);
    };
}
#endif
