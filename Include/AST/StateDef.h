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
        Expr* base;///<Base Of the State.
        StateDef(Location _loc, StmtBlock* _stmts, Expr* _base = nullptr) : Expr(_loc), stmts(_stmts), base(_base) {}
        void visit(Visitor* that);
        ~StateDef();
    };
}
#endif
