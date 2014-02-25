#ifndef ST_1928392012_AST_STMTBLOCK
#define ST_1928392012_AST_STMTBLOCK
#include "Stmt.h"
#include <vector>
#include "XList.h"
namespace AST {
    /**AST for Statement's Block.*/
    class StmtBlock : public Stmt {
    public:
        std::vector<Stmt*> stmts;///<Statements in block.
        StmtBlock(Location _loc, StmtList* _stmts) : Stmt(_loc) {StmtList::FillVector(_stmts, stmts);}
        void visit(Visitor* that);
        ~StmtBlock();
    };
}
#endif

