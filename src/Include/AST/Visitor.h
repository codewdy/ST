#ifndef ST_9348212392_AST_VISITOR
#define ST_9348212392_AST_VISITOR
namespace AST {
    class AST;
    class Integer;
    class Double;
    class String;
    class Program;
    class SimpleStmt;
    class ForStmt;
    class WhileStmt;
    class IfStmt;
    class StmtBlock;
    class ListExpr;
    class CallExpr;
    class DoubleOperExpr;
    class SingleOperExpr;
    class VarLValue;
    class ArrayAtLValue;
    
    class Visitor {
    public:
        void visit(AST* that);
        virtual void visitInteger(Integer* that);
        virtual void visitDouble(Double* that);
        virtual void visitString(String* that);
        virtual void visitProgram(Program* that);
        virtual void visitSimpleStmt(SimpleStmt* that);
        virtual void visitForStmt(ForStmt* that);
        virtual void visitWhileStmt(WhileStmt* that);
        virtual void visitIfStmt(IfStmt* stmt);
        virtual void visitStmtBlock(StmtBlock* that);
        virtual void visitListExpr(ListExpr* that);
        virtual void visitCallExpr(CallExpr* that);
        virtual void visitDoubleOperExpr(DoubleOperExpr* that);
        virtual void visitSingleOperExpr(SingleOperExpr* that);
        virtual void visitVarLValue(VarLValue* that);
        virtual void visitArrayAtLValue(ArrayAtLValue* that);
    };
}
#endif
