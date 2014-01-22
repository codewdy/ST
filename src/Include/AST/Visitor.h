#ifndef ST_9348212392_AST_VISITOR
#define ST_9348212392_AST_VISITOR
#define DefVisitClass(CLASS) virtual void visit##CLASS(CLASS* that);
#define DefVisitASTClass(CLASS) virtual void visit##CLASS(AST::CLASS* that);
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
        DefVisitClass(Integer)
        DefVisitClass(Double)
        DefVisitClass(String)
        DefVisitClass(Program)
        DefVisitClass(SimpleStmt)
        DefVisitClass(ForStmt)
        DefVisitClass(WhileStmt)
        DefVisitClass(IfStmt)
        DefVisitClass(StmtBlock)
        DefVisitClass(ListExpr)
        DefVisitClass(CallExpr)
        DefVisitClass(DoubleOperExpr)
        DefVisitClass(SingleOperExpr)
        DefVisitClass(VarLValue)
        DefVisitClass(ArrayAtLValue)
    };
}
#endif
