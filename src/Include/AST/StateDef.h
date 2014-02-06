#ifndef ST_8394839210_AST_STATEDEF
#define ST_8394839210_AST_STATEDEF
#include "Expr.h"
#include <vector>
namespace AST
{
    class StmtBlock;
    /**AST for State Definition.*/
    class StateDef : public Expr {
    protected:
        StateDef();
        StateDef(const StateDef&);
    public:
        StmtBlock* stmts;///<State Def Statement.
        StateDef(Location _loc, StmtBlock* _stmts) : Expr(_loc), stmts(_stmts) {}
        void visit(Visitor* that);
        ~StateDef();
    };
}
#endif
