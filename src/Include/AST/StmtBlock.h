#ifndef ST_1928392012_AST_STMTBLOCK
#define ST_1928392012_AST_STMTBLOCK
#include "Stmt.h"
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
        static StmtBlock* Create(Oper* s1, StmtList* s2, Oper* s3);
    };
}
#endif

