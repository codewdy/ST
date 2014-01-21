#ifndef ST_5391073821_AST_SIMPLESTMT
#define ST_5391073821_AST_SIMPLESTMT
#include "Stmt.h"
namespace AST
{
    class Expr;
    class SimpleStmt : public Stmt
    {
    protected:
        SimpleStmt();
        SimpleStmt(const SimpleStmt&);
    public:
        Expr* expr;
        static SimpleStmt* Create(Expr* _e);
        void visit(Visitor* that);
    };
}
#endif
