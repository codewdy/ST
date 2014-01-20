#ifndef ST_2933102910_AST_FORSTMT
#define ST_2933102910_AST_FORSTMT
#include "Stmt.h"
namespace AST
{
    class Keyword;
    class Oper;
    class Identifier;
    class Expr;
    class Stmt;
    class ForStmt : public Stmt {
    protected:
        ForStmt();
        ForStmt(const ForStmt&);
    public:
        Identifier* var;
        Expr* set;
        Stmt* loop;
        static ForStmt* Create(Keyword* s1, Oper* s2, Identifier* s3, Oper* s4, Expr* s5, Oper* s6, Stmt* s7);
        void visit(Visitor* that);
    };
}
#endif
