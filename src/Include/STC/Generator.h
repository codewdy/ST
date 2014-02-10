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
            _break = nullptr;
            return visitX(that).beg;
        }

        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(Integer)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(Double)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(String)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(Program)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(SimpleStmt)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(ForStmt)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(WhileStmt)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(IfStmt)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(StmtBlock)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(BreakStmt)
        /**sp = sp.*/
        ST_DEF_VISIT_AST_CLASS(ReturnStmt)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(ListExpr)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(CallExpr)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(FuncDef)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(StateDef)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(GlobalExpr)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(LocaleExpr)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(NullExpr)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(DoubleOperExpr)
        /**sp = sp + 1.*/
        ST_DEF_VISIT_AST_CLASS(SingleOperExpr)
        /**-RValue : sp = sp + 1
         * -LValue : sp = sp - 1.*/
        ST_DEF_VISIT_AST_CLASS(VarLValue)
        /**-RValue : sp = sp + 1
         * -LValue : sp = sp - 1.*/
        ST_DEF_VISIT_AST_CLASS(ArrayAtLValue)
    };
}
#endif
