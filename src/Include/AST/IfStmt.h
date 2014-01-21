#ifndef ST_7832812358_AST_IFSTMT
#define ST_7832812358_AST_IFSTMT
#include "Stmt.h"
namespace AST {
    class Expr;
    class IfStmt : public Stmt {
    protected:
        IfStmt();
        IfStmt(const IfStmt&);
    public:
        Expr* condition;
        Stmt *yes, *no;
        static IfStmt* Create(Expr* _condition, Stmt* _yes);
        static IfStmt* Create(Expr* _condition, Stmt* _yes, Stmt* _no);
        void visit(Visitor* that);
    };
}
#endif

