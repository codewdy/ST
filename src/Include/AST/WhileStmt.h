#ifndef ST_0901238293_AST_WHILESTMT
#define ST_0901238293_AST_WHILESTMT
#include "Stmt.h"
namespace AST {
    class Keyword;
    class Oper;
    class Expr;
    class WhileStmt : public Stmt {
    protected:
        WhileStmt();
        WhileStmt(const WhileStmt&);
    public:
        Expr* condition;
        Stmt* loop;
        static WhileStmt* Create(Expr* _condition, Stmt* _loop);
        void visit(Visitor* that);
    };
}
#endif

