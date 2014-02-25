#ifndef ST_0901238293_AST_WHILESTMT
#define ST_0901238293_AST_WHILESTMT
#include "Stmt.h"
namespace AST {
    class Expr;
    /**AST for While Statement.*/
    class WhileStmt : public Stmt {
    public:
        Expr* condition;///<Condition for the loop.
        Stmt* loop;///<Running Code for the while loop.
        WhileStmt(Location _loc, Expr* _condition, Stmt* _loop) : Stmt(_loc), condition(_condition), loop(_loop) {}
        void visit(Visitor* that);
        ~WhileStmt();
    };
}
#endif

