#ifndef ST_9374215834_STC_GENERATOR
#define ST_9374215834_STC_GENERATOR
#include "STC.h"
#include "AST/Visitor.h"
#include "AST/Program.h"

namespace STC {
    /**Generate STC From AST.*/
    class Generator : public AST::Visitor {
        /**the ret of every visit call. every visit method should change this to return.*/
        STCList _ret;
        /**the mode of the visit call run on. every visit call should change it before.*/
        enum Mode {
            LValue, RValue
        } _mode;
        /**The break will jump to this STC.*/
        STC* _break;
    public:
        /**the interface of the visit.*/
        STCList visitX(AST::AST* that, Mode mode = RValue) {
            _mode = mode;
            visit(that);
            return _ret;
        }

        /**Generate A Program.*/
        STC* Gen(AST::Program* that) {
            _break = 0;
            return visitX(that).beg;
        }

        /**sp = sp + 1.*/
        DefVisitASTClass(Integer)
        /**sp = sp + 1.*/
        DefVisitASTClass(Double)
        /**sp = sp + 1.*/
        DefVisitASTClass(String)
        /**sp = sp.*/
        DefVisitASTClass(Program)
        /**sp = sp.*/
        DefVisitASTClass(SimpleStmt)
        /**sp = sp.*/
        DefVisitASTClass(ForStmt)
        /**sp = sp.*/
        DefVisitASTClass(WhileStmt)
        /**sp = sp.*/
        DefVisitASTClass(IfStmt)
        /**sp = sp.*/
        DefVisitASTClass(StmtBlock)
        /**sp = sp.*/
        DefVisitASTClass(BreakStmt)
        /**sp = sp.*/
        DefVisitASTClass(ReturnStmt)
        /**sp = sp + 1.*/
        DefVisitASTClass(ListExpr)
        /**sp = sp + 1.*/
        DefVisitASTClass(CallExpr)
        /**sp = sp + 1.*/
        DefVisitASTClass(FuncDef)
        /**sp = sp + 1.*/
        DefVisitASTClass(StateDef)
        /**sp = sp + 1.*/
        DefVisitASTClass(GlobalExpr)
        /**sp = sp + 1.*/
        DefVisitASTClass(LocaleExpr)
        /**sp = sp + 1.*/
        DefVisitASTClass(NullExpr)
        /**sp = sp + 1.*/
        DefVisitASTClass(DoubleOperExpr)
        /**sp = sp + 1.*/
        DefVisitASTClass(SingleOperExpr)
        /**-RValue : sp = sp + 1
         * -LValue : sp = sp - 1.*/
        DefVisitASTClass(VarLValue)
        /**-RValue : sp = sp + 1
         * -LValue : sp = sp - 1.*/
        DefVisitASTClass(ArrayAtLValue)
    };
}
#endif
