#ifndef ST_8392618393_AST_PROGRAM
#define ST_8392618393_AST_PROGRAM
#include "AST.h"
#include <vector>
namespace AST {
    class StmtList;
    class Stmt;
    class Program : public AST {
    protected:
        Program(Location _loc);
        Program(const Program&);
    public:
        std::vector<Stmt*> stmts;
        static Program* Create(StmtList* _stmts);
        void visit(Visitor* v);
    };
}
#endif
