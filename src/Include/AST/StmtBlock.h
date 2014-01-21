#ifndef ST_1928392012_AST_STMTBLOCK
#define ST_1928392012_AST_STMTBLOCK
#include "Stmt.h"
#include <vector>
namespace AST
{
    class StmtList;
    class StmtBlock : public Stmt
    {
    protected:
        StmtBlock();
        StmtBlock(const StmtBlock&);
    public:
        std::vector<Stmt*> stmts;
        static StmtBlock* Create(StmtList* _stmts);
        void visit(Visitor* that);
    };
}
#endif

