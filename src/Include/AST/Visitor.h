#ifndef ST_9348212392_AST_VISITOR
#define ST_9348212392_AST_VISITOR
/**Define visitClass In Namespace AST.*/
#define DefVisitClass(CLASS) virtual void visit##CLASS(CLASS* that);
/**Define visitClass Out Of Namespace AST.*/
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
    class BreakStmt;
    class ListExpr;
    class CallExpr;
    class DoubleOperExpr;
    class SingleOperExpr;
    class VarLValue;
    class ArrayAtLValue;
    class FuncDef;
    class StateDef;
    class GlobalExpr;
    class LocaleExpr;
    
    /**Base Object For Visitor Pattern.*/
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
        DefVisitClass(BreakStmt)
        DefVisitClass(ListExpr)
        DefVisitClass(CallExpr)
        DefVisitClass(FuncDef)
        DefVisitClass(StateDef)
        DefVisitClass(GlobalExpr)
        DefVisitClass(LocaleExpr)
        DefVisitClass(DoubleOperExpr)
        DefVisitClass(SingleOperExpr)
        DefVisitClass(VarLValue)
        DefVisitClass(ArrayAtLValue)
        virtual ~Visitor();
    };
}
#endif
