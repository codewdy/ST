#ifndef ST_8394839210_AST_STATEDEF
#define ST_8394839210_AST_STATEDEF
#include "Expr.h"
#include <vector>
#include "XList.h"
namespace AST
{
    class StmtBlock;
    class LValue;
    /**AST for State Definition.*/
    class StateDef : public Expr {
    protected:
        StateDef();
        StateDef(const StateDef&);
    public:
        std::vector<LValue*> states;///<State Names.
        StmtBlock* stmts;///<State Def Statement.
        StateDef(Location _loc, LValueList* _states, StmtBlock* _stmts) : Expr(_loc), stmts(_stmts) {LValueList::FillVector(_states, states);}
        void visit(Visitor* that);
        ~StateDef();
    };
}
#endif
