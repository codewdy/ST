#ifndef ST_1928392012_AST_STMTBLOCK
#define ST_1928392012_AST_STMTBLOCK
#include "Stmt.h"
#include <vector>
namespace AST
{
    class Oper;
    class StmtList;
    class StmtBlock : public Stmt
    {
    protected:
        StmtBlock();
        StmtBlock(const StmtBlock&);
    public:
        std::vector<Stmt*> stmts;
        static StmtBlock* Create(Oper* s1, StmtList* s2, Oper* s3);
        void visit(Visitor* that);
    };
}
#endif

