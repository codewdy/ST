#include "AST/ALL.h"

class ASTPrinter : public AST::Visitor {
    int depth;
    std::ostream& fout;
public:
    ASTPrinter(std::ostream& _fout) : depth(0), fout(_fout) {} 
    void visitProgram(AST::Program* that);
    void visitSimpleStmt(AST::SimpleStmt* that);
    void visitDoubleOperExpr(AST::SimpleStmt* that);
    void visitVarLValue(AST::VarLValue* that);
    void visitDouble(AST::Double that);
    void visitInteger(AST::Integer that);
    void visitString(AST::String that);
};

