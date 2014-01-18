#ifndef ST_8394839210_AST_STATEDEF
#define ST_8394839210_AST_STATEDEF
#include "Expr.h"
namespace AST
{
    class Keyword;
    class IDs;
    class StmtBlock;
    class StateDef : public Expr {
    protected:
        StateDef();
        StateDef(const StateDef&);
    public:
        static StateDef* Create(Keyword* s1, IDs* s2, StmtBlock* s3);
    };
}
#endif
