#include "AST/ALL.h"
#include "STC/ALL.h"
#include <unordered_map>
#define RETURN(VAR) do {_ret = VAR;return;} while (0)

namespace STC {
    void Generator::visitInteger(AST::Integer* that) {
        RETURN(STC::CreatePushInteger(that->str));
    }

    void Generator::visitDouble(AST::Double* that) {
        RETURN(STC::CreatePushDouble(that->str));
    }

    void Generator::visitString(AST::String* that) {
        RETURN(STC::CreatePushString(that->str));
    }

    void Generator::visitProgram(AST::Program* that) {
        STCList ret;
        if (that->stmts.size() == 0)
            ret = STC::CreateNop();
        else
            for (auto stmt : that->stmts)
                ret.Append(visitX(stmt));
        RETURN(ret);
    }

    void Generator::visitSimpleStmt(AST::SimpleStmt* that) {
        RETURN(visitX(that->expr).Append(STC::CreatePop()));
    }

    void Generator::visitForStmt(AST::ForStmt* that) {
        STCList ret;
        STC* end = STC::CreatePop();
        STC* o_break = _break;
        _break = end;
        //top=set.__iter__
        ret.Append(visitX(that->set));
        ret.Append(STC::CreateGetAttr("__iter__"));
        ret.Append(STC::CreateCall(0));
        //TestNotEND
        STC* loopBeg = STC::CreateCopyTop();
        ret.Append(loopBeg);
        ret.Append(STC::CreateGetAttr("__isEnd__"));
        ret.Append(STC::CreateCall(0));
        ret.Append(STC::CreateTrueGoto(end));
        //Assign to loop
        ret.Append(STC::CreateCopyTop());
        ret.Append(STC::CreateGetAttr("__getElement__"));
        ret.Append(STC::CreateCall(0));
        ret.Append(visitX(that->var, LValue));
        ret.Append(visitX(that->loop));
        //Get Next
        ret.Append(STC::CreateGetAttr("__next__"));
        ret.Append(STC::CreateCall(0));
        ret.Append(STC::CreateGoto(loopBeg));
        ret.Append(end);
        _break = o_break;
        RETURN(ret);
    }

    void Generator::visitWhileStmt(AST::WhileStmt* that) {
        STCList ret;
        STC* end = STC::CreateNop();
        STC* o_break = _break;
        _break = end;
        ret.Append(visitX(that->condition));
        ret.Append(STC::CreateFalseGoto(end));
        ret.Append(visitX(that->loop));
        ret.Append(STC::CreateGoto(ret.beg));
        ret.Append(end);
        _break = o_break;
        RETURN(ret);
    }

    void Generator::visitIfStmt(AST::IfStmt* that) {
        STCList ret;
        ret.Append(visitX(that->condition));
        STC* end = STC::CreateNop();
        if (that->no) {
            STCList yes = visitX(that->yes);
            STCList no = visitX(that->no);
            ret.Append(STC::CreateFalseGoto(no.beg));
            ret.Append(yes);
            ret.Append(STC::CreateGoto(end));
            ret.Append(no);
            ret.Append(end);
        } else {
            ret.Append(STC::CreateFalseGoto(end));
            ret.Append(visitX(that->yes));
            ret.Append(end);
        }
        RETURN(ret);
    }

    void Generator::visitStmtBlock(AST::StmtBlock* that) {
        STCList ret;
        if (that->stmts.size() == 0)
            ret = STC::CreateNop();
        else
            for (auto stmt : that->stmts)
                ret.Append(visitX(stmt));
        RETURN(ret);
    }
    void Generator::visitBreakStmt(AST::BreakStmt* that) {
        if (_break == 0) {
            //TODO: ADD A Exception For Noncotrolled break.
        } else {
            RETURN(STC::CreateGoto(_break));
        }
    }

    void Generator::visitReturnStmt(AST::ReturnStmt* that) {
        STCList ret;
        if (that->expr) {
            ret.Append(visitX(that->expr));
        } else {
            ret.Append(STC::CreatePushNull());
        }
        ret.Append(STC::CreateReturn());
        RETURN(ret);
    }

    void Generator::visitListExpr(AST::ListExpr* that) {
        STCList ret;
        for (int i = that->exprs.size() - 1; i >= 0; i--)
            ret.Append(visitX(that->exprs[i]));
        ret.Append(STC::CreateMakeList(that->exprs.size()));
        RETURN(ret);
    }

    void Generator::visitCallExpr(AST::CallExpr* that) {
        STCList ret;
        for (int i = that->parms.size() - 1; i >= 0; i--)
            ret.Append(visitX(that->parms[i]));
        ret.Append(visitX(that->func));
        RETURN(ret);
    }

    void Generator::visitFuncDef(AST::FuncDef* that) {
        STCList ret;
        STC* o_break = _break;
        _break = 0;
        STCList func = visitX(that->stmts);
        func.Append(STC::CreatePushNull());
        func.Append(STC::CreateReturn());
        ret.Append(STC::CreateDefFunc(func.beg));
        _break = o_break;
        for (int i = that->funcs.size() - 1; i >= 0; i--) {
            ret.Append(STC::CreateCopyTop());
            ret.Append(visitX(that->funcs[i], LValue));
        }
        RETURN(ret);
    }

    void Generator::visitStateDef(AST::StateDef* that) {
        STCList ret;
        STC* o_break = _break;
        _break = 0;
        ret.Append(STC::CreateDefState(visitX(that->stmts).beg));
        _break = o_break;
        for (int i = that->states.size() - 1; i >= 0; i--) {
            ret.Append(STC::CreateCopyTop());
            ret.Append(visitX(that->states[i], LValue));
        }
        RETURN(ret);
    }

    void Generator::visitGlobalExpr(AST::GlobalExpr* that) {
        RETURN(STC::CreatePushGlobal());
    }

    void Generator::visitLocaleExpr(AST::LocaleExpr* that) {
        RETURN(STC::CreatePushLocale());
    }

    void Generator::visitNullExpr(AST::NullExpr* that) {
        RETURN(STC::CreatePushNull());
    }

    static std::unordered_map<int, std::string> DBOperTrans = {
        {AST::DoubleOperExpr::PLUS, "add"},
        {AST::DoubleOperExpr::MINUS, "minus"},
        {AST::DoubleOperExpr::MUL, "mul"},
        {AST::DoubleOperExpr::DIV, "div"},
        {AST::DoubleOperExpr::MOD, "mod"},
        {AST::DoubleOperExpr::AND, "and"},
        {AST::DoubleOperExpr::OR, "or"},
        {AST::DoubleOperExpr::LT, "less_than"},
        {AST::DoubleOperExpr::GT, "greater_than"},
        {AST::DoubleOperExpr::LE, "not_greater"},
        {AST::DoubleOperExpr::GE, "not_less"},
        {AST::DoubleOperExpr::GE, "equal"},
        {AST::DoubleOperExpr::GE, "not_equal"},
    };
    
    void Generator::visitDoubleOperExpr(AST::DoubleOperExpr* that) {
        STCList ret;
        ret.Append(visitX(that->expr2));
        if (that->oper == AST::DoubleOperExpr::ASG) {
            ret.Append(STC::CreateCopyTop());
            ret.Append(visitX(that->expr1, LValue));
        } else {
            ret.Append(visitX(that->expr1));
            ret.Append(STC::CreateGetAttr("__" + DBOperTrans[that->oper] + "__"));
            ret.Append(STC::CreateCall(1));
        }
        RETURN(ret);
    }

    static std::unordered_map<int, std::string> SGOperTrans = {
        {AST::SingleOperExpr::NEG, "neg"},
        {AST::SingleOperExpr::NOT, "not"},
    };

    void Generator::visitSingleOperExpr(AST::SingleOperExpr* that) {
        STCList ret;
        ret.Append(visitX(that->expr1));
        ret.Append(STC::CreateGetAttr("__" + SGOperTrans[that->oper] + "__"));
        ret.Append(STC::CreateCall(0));
        RETURN(ret);
    }

    void Generator::visitVarLValue(AST::VarLValue* that) {
        STCList ret;
        if (_mode == LValue) {
            ret.Append(visitX(that->obj));
            ret.Append(STC::CreateSetAttr(that->attr));
        } else {
            ret.Append(visitX(that->obj));
            ret.Append(STC::CreateGetAttr(that->attr));
        }
        RETURN(ret);
    }

    void Generator::visitArrayAtLValue(AST::ArrayAtLValue* that) {
        STCList ret;
        if (_mode == LValue) {
            ret.Append(visitX(that->index));
            ret.Append(visitX(that->array));
            ret.Append(STC::CreateGetAttr("__set_element__"));
            ret.Append(STC::CreateCall(2));
        } else {
            ret.Append(visitX(that->index));
            ret.Append(visitX(that->array));
            ret.Append(STC::CreateGetAttr("__get_element__"));
            ret.Append(STC::CreateCall(1));
        }
    }
}
