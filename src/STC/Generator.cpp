#include "AST/ALL.h"
#include "STC/ALL.h"
#include <unordered_map>
#include "Exception.h"
#define ST_RETURN(VAR) do {_ret = VAR;return;} while (0)

namespace STC {
    void Generator::visitInteger(AST::Integer* that) {
        ST_RETURN(STC::CreatePushInteger(that->str));
    }

    void Generator::visitDouble(AST::Double* that) {
        ST_RETURN(STC::CreatePushDouble(that->str));
    }

    void Generator::visitString(AST::String* that) {
        ST_RETURN(STC::CreatePushString(that->str));
    }

    void Generator::visitProgram(AST::Program* that) {
        STCList ret;
        ret.Append(STC::CreateSourceFile(*that->loc.str));
        if (that->stmts.size() == 0)
            ret = STC::CreateNop();
        else
            for (auto stmt : that->stmts)
                ret.Append(visitX(stmt));
        ST_RETURN(ret);
    }

    void Generator::visitSimpleStmt(AST::SimpleStmt* that) {
        STCList ret;
        ret.Append(STC::CreateSourceLine(that->loc.lineno));
        ret.Append(visitX(that->expr));
        ret.Append(STC::CreatePop());
        ST_RETURN(ret);
    }

    void Generator::visitForStmt(AST::ForStmt* that) {
        STCList ret;
        STC* end = STC::CreatePop();
        STC* o_break = _break;
        _break = end;
        //top=set.__iter__
        ret.Append(STC::CreateSourceLine(that->loc.lineno));
        ret.Append(visitX(that->set));
        ret.Append(STC::CreateGetAttr("__iter__"));
        ret.Append(STC::CreateCall(0));
        //TestNotEND
        STC* loopBeg = STC::CreateCopyTop();
        ret.Append(loopBeg);
        ret.Append(STC::CreateGetAttr("__is_end__"));
        ret.Append(STC::CreateCall(0));
        ret.Append(STC::CreateTrueGoto(end));
        //Assign to loop
        ret.Append(STC::CreateCopyTop());
        ret.Append(STC::CreateGetAttr("__get__"));
        ret.Append(STC::CreateCall(0));
        ret.Append(visitX(that->var, LValue));
        ret.Append(visitX(that->loop));
        ret.Append(STC::CreateSourceLine(that->loc.lineno));
        //Get Next
        ret.Append(STC::CreateGetAttr("__next__"));
        ret.Append(STC::CreateCall(0));
        ret.Append(STC::CreateGoto(loopBeg));
        ret.Append(end);
        _break = o_break;
        ST_RETURN(ret);
    }

    void Generator::visitWhileStmt(AST::WhileStmt* that) {
        STCList ret;
        STC* end = STC::CreateNop();
        STC* o_break = _break;
        _break = end;
        ret.Append(STC::CreateSourceLine(that->loc.lineno));
        ret.Append(visitX(that->condition));
        ret.Append(STC::CreateFalseGoto(end));
        ret.Append(visitX(that->loop));
        ret.Append(STC::CreateSourceLine(that->loc.lineno));
        ret.Append(STC::CreateGoto(ret.beg));
        ret.Append(end);
        _break = o_break;
        ST_RETURN(ret);
    }

    void Generator::visitIfStmt(AST::IfStmt* that) {
        STCList ret;
        ret.Append(visitX(that->condition));
        STC* end = STC::CreateNop();
        if (that->no) {
            STCList yes = visitX(that->yes);
            STCList no = visitX(that->no);
            ret.Append(STC::CreateSourceLine(that->loc.lineno));
            ret.Append(STC::CreateFalseGoto(no.beg));
            ret.Append(yes);
            ret.Append(STC::CreateGoto(end));
            ret.Append(no);
            ret.Append(end);
        } else {
            ret.Append(STC::CreateSourceLine(that->loc.lineno));
            ret.Append(STC::CreateFalseGoto(end));
            ret.Append(visitX(that->yes));
            ret.Append(end);
        }
        ST_RETURN(ret);
    }

    void Generator::visitStmtBlock(AST::StmtBlock* that) {
        STCList ret;
        if (that->stmts.size() == 0)
            ret = STC::CreateNop();
        else
            for (auto stmt : that->stmts)
                ret.Append(visitX(stmt));
        ST_RETURN(ret);
    }
    void Generator::visitBreakStmt(AST::BreakStmt* that) {
        if (_break == nullptr) {
            ST_RAISE(Break, that->loc);
        } else {
            ST_RETURN(STC::CreateGoto(_break));
        }
    }

    void Generator::visitReturnStmt(AST::ReturnStmt* that) {
        STCList ret;
        ret.Append(STC::CreateSourceLine(that->loc.lineno));
        if (that->expr) {
            ret.Append(visitX(that->expr));
        } else {
            ret.Append(STC::CreatePushNull());
        }
        ret.Append(STC::CreateReturn());
        ST_RETURN(ret);
    }

    void Generator::visitListExpr(AST::ListExpr* that) {
        STCList ret;
        for (int i = that->exprs.size() - 1; i >= 0; i--)
            ret.Append(visitX(that->exprs[i]));
        ret.Append(STC::CreateMakeList(that->exprs.size()));
        ST_RETURN(ret);
    }

    void Generator::visitCallExpr(AST::CallExpr* that) {
        STCList ret;
        for (int i = that->parms.size() - 1; i >= 0; i--)
            ret.Append(visitX(that->parms[i]));
        ret.Append(visitX(that->func));
        ret.Append(STC::CreateCall(that->parms.size()));
        ST_RETURN(ret);
    }

    void Generator::visitFuncDef(AST::FuncDef* that) {
        STCList ret;
        STC* o_break = _break;
        _break = nullptr;
        STCList func = visitX(that->stmts);
        func.Append(STC::CreatePushNull());
        func.Append(STC::CreateReturn());
        for (auto arg : that->args)
            ret.Append(STC::STC::CreateFuncArg(arg));
        ret.Append(STC::CreateDefFunc(func.beg));
        _break = o_break;
        ST_RETURN(ret);
    }

    void Generator::visitStateDef(AST::StateDef* that) {
        STCList ret;
        STC* o_break = _break;
        _break = nullptr;
        ret.Append(STC::CreateDefState(visitX(that->stmts).beg));
        _break = o_break;
        ST_RETURN(ret);
    }

    void Generator::visitGlobalExpr(AST::GlobalExpr* that) {
        ST_RETURN(STC::CreatePushGlobal());
    }

    void Generator::visitLocaleExpr(AST::LocaleExpr* that) {
        ST_RETURN(STC::CreatePushLocale());
    }

    void Generator::visitNullExpr(AST::NullExpr* that) {
        ST_RETURN(STC::CreatePushNull());
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
        {AST::DoubleOperExpr::EQ, "equal"},
        {AST::DoubleOperExpr::NE, "not_equal"},
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
        ST_RETURN(ret);
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
        ST_RETURN(ret);
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
        ST_RETURN(ret);
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
        ST_RETURN(ret);
    }
}
