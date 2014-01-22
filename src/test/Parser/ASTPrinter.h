#include "AST/ALL.h"
#include <string>
#include <iostream>

class ASTPrinter : public AST::Visitor {
    std::string prefix;
    std::ostream& fout;
public:
    ASTPrinter(std::ostream& _fout) : prefix(""), fout(_fout) {} 
    DefVisitASTClass(Program)
    DefVisitASTClass(SimpleStmt)
    DefVisitASTClass(DoubleOperExpr)
    DefVisitASTClass(VarLValue)
    DefVisitASTClass(Double)
    DefVisitASTClass(Integer)
    DefVisitASTClass(String)
};

