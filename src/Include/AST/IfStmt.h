#ifndef ST_7832812358_AST_IFSTMT
#define ST_7832812358_AST_IFSTMT
#include "Stmt.h"
namespace AST {
    class Expr;
    /**AST for the If Statement.*/
    class IfStmt : public Stmt {
    public:
        Expr* condition;///<the condition
        Stmt *yes;///<Statement when condition is true.
        Stmt *no;///<Statement when condition is false.
        IfStmt(Location _loc, Expr* _condition, Stmt* _yes, Stmt* _no = 0) : Stmt(_loc), condition(_condition), yes(_yes), no(_no) {}
        void visit(Visitor* that);
        ~IfStmt();
    };
}
#endif

