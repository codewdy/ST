#ifndef ST_9348212392_AST_VISITOR
#define ST_9348212392_AST_VISITOR
/**Define visitClass In Namespace AST.*/
#define ST_DEF_VISIT_CLASS(CLASS) virtual void visit##CLASS(CLASS* that);
/**Define visitClass Out Of Namespace AST.*/
#define ST_DEF_VISIT_AST_CLASS(CLASS) virtual void visit##CLASS(AST::CLASS* that);
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
    class ReturnStmt;
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
    class NullExpr;
    
    /**Base Object For Visitor Pattern.*/
    class Visitor {
    public:
        void visit(AST* that);
        ST_DEF_VISIT_CLASS(Integer)
        ST_DEF_VISIT_CLASS(Double)
        ST_DEF_VISIT_CLASS(String)
        ST_DEF_VISIT_CLASS(Program)
        ST_DEF_VISIT_CLASS(SimpleStmt)
        ST_DEF_VISIT_CLASS(ForStmt)
        ST_DEF_VISIT_CLASS(WhileStmt)
        ST_DEF_VISIT_CLASS(IfStmt)
        ST_DEF_VISIT_CLASS(StmtBlock)
        ST_DEF_VISIT_CLASS(BreakStmt)
        ST_DEF_VISIT_CLASS(ReturnStmt)
        ST_DEF_VISIT_CLASS(ListExpr)
        ST_DEF_VISIT_CLASS(CallExpr)
        ST_DEF_VISIT_CLASS(FuncDef)
        ST_DEF_VISIT_CLASS(StateDef)
        ST_DEF_VISIT_CLASS(GlobalExpr)
        ST_DEF_VISIT_CLASS(LocaleExpr)
        ST_DEF_VISIT_CLASS(NullExpr)
        ST_DEF_VISIT_CLASS(DoubleOperExpr)
        ST_DEF_VISIT_CLASS(SingleOperExpr)
        ST_DEF_VISIT_CLASS(VarLValue)
        ST_DEF_VISIT_CLASS(ArrayAtLValue)
        virtual ~Visitor();
    };
}
#endif
