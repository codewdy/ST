#ifndef ST_7182369121_AST_RETURNSTMT
#define ST_7182369121_AST_RETURNSTMT
#include "Stmt.h"
namespace AST {
    class Expr;
    /**AST for Return Statement.*/
    class ReturnStmt : public Stmt {
    public:
        Expr* expr;//<expr for return.
        ReturnStmt(Location _loc, Expr* _expr = nullptr) : Stmt(_loc), expr(_expr) {}
        void visit(Visitor* that);
        ~ReturnStmt();
    };
}
#endif
