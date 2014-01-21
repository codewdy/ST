#ifndef ST_8291827482_AST_FUNCDEF
#define ST_8291827482_AST_FUNCDEF
#include "Expr.h"
#include <vector>
#include <string>
namespace AST
{
    class LValueList;
    class IDList;
    class StmtBlock;
    class LValue;
    class FuncDef : public Expr
    {
    protected:
        FuncDef();
    public:
        std::vector<LValue*> funcs;
        std::vector<std::string> args;
        StmtBlock* stmts;
        static FuncDef* Create(LValueList* _funcs, IDList* _args, StmtBlock* _stmts);
    };
}
#endif
