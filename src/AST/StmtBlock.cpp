#include "AST/StmtBlock.h"
#include "AST/Visitor.h"

namespace AST {
    void StmtBlock::visit(Visitor* that) {
        that->visitStmtBlock(this);
    }
}
