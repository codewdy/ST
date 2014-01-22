#ifndef ST_8392618393_AST_PROGRAM
#define ST_8392618393_AST_PROGRAM
#include "AST.h"
#include "XList.h"
#include <vector>
namespace AST {
    class Stmt;
    class Program : public AST {
    public:
        std::vector<Stmt*> stmts;
        Program(Location _loc, StmtList* _stmts) : AST(_loc) {StmtList::FillVector(_stmts, stmts);}
        void visit(Visitor* v);
    };
}
#endif
