#ifndef ST_8394839210_AST_STATEDEF
#define ST_8394839210_AST_STATEDEF
#include "Expr.h"
#include <vector>
namespace AST
{
    class LValueList;
    class StmtBlock;
    class LValue;
    class StateDef : public Expr {
    protected:
        StateDef();
        StateDef(const StateDef&);
    public:
        std::vector<LValue*> states;
        StmtBlock* stmts;
        static StateDef* Create(LValueList* _states, StmtBlock* stmts);
    };
}
#endif
