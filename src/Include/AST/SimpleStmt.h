#ifndef ST_5391073821_AST_SIMPLESTMT
#define ST_5391073821_AST_SIMPLESTMT
#include "Stmt.h"
namespace AST {
    class Expr;
    class SimpleStmt : public Stmt {
    public:
        Expr* expr;
        SimpleStmt(Location _loc, Expr* _expr) : Stmt(_loc), expr(_expr) {}
        void visit(Visitor* that);
        ~SimpleStmt();
    };
}
#endif
