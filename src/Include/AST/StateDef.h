#ifndef ST_8394839210_AST_STATEDEF
#define ST_8394839210_AST_STATEDEF
#include "Expr.h"
#include <vector>
#include "XList.h"
namespace AST
{
    class StmtBlock;
    class LValue;
    class StateDef : public Expr {
    protected:
        StateDef();
        StateDef(const StateDef&);
    public:
        std::vector<LValue*> states;
        StmtBlock* stmts;
        StateDef(Location _loc, LValueList* _states, StmtBlock* _stmts) : Expr(_loc), stmts(_stmts) {LValueList::FillVector(_states, states);}
    };
}
#endif
