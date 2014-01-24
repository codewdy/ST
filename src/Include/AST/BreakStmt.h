#ifndef ST_9823412309_AST_BREAKSTMT
#define ST_9823412309_AST_BREAKSTMT
#include "Stmt.h"
namespace AST {
    /**AST for Break Statement.*/
    class BreakStmt : public Stmt {
    public:
        BreakStmt(Location _loc) : Stmt(_loc) {}
        void visit(Visitor* that);
    };
}
#endif
