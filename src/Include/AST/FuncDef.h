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
    /**AST for the Function Definition*/
    class FuncDef : public Expr
    {
    public:
        std::vector<LValue*> funcs;///<Func Names.
        std::vector<std::string> args;///<Func Arguments.
        StmtBlock* stmts;///<Func Codes.
        FuncDef(Location _loc, LValueList* _funcs, IDList* _args, StmtBlock* _stmts) : Expr(_loc), stmts(_stmts) {
            LValueList::FillVector(_funcs, funcs);
            IDList::FillVector(_args, args);
        }
        void visit(Visitor* that);
        ~FuncDef();
    };
}
#endif
