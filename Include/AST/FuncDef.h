#ifndef ST_8291827482_AST_FUNCDEF
#define ST_8291827482_AST_FUNCDEF
#include "Expr.h"
#include <vector>
#include <string>
#include "XList.h"
namespace AST
{
    class StmtBlock;
    /**AST for the Function Definition*/
    class FuncDef : public Expr
    {
    public:
        std::vector<std::string> args;///<Func Arguments.
        StmtBlock* stmts;///<Func Codes.
        FuncDef(Location _loc, IDList* _args, StmtBlock* _stmts) : Expr(_loc), stmts(_stmts) {
            IDList::FillVector(_args, args);
        }
        void visit(Visitor* that);
        ~FuncDef();
    };
}
#endif
