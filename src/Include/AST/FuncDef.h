#ifndef ST_8291827482_AST_FUNCDEF
#define ST_8291827482_AST_FUNCDEF
#include "Expr.h"
#include <vector>
#include <string>
#include "XList.h"
namespace AST
{
    class StmtBlock;
    class LValue;
    class FuncDef : public Expr
    {
    public:
        std::vector<LValue*> funcs;
        std::vector<std::string> args;
        StmtBlock* stmts;
        FuncDef(Location _loc, LValueList* _funcs, IDList* _args, StmtBlock* _stmts) : Expr(_loc), stmts(_stmts) {
            LValueList::FillVector(_funcs, funcs);
            IDList::FillVector(_args, args);
        }
        void visit(Visitor* that);
    };
}
#endif
