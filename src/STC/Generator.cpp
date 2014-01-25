#include "AST/ALL.h"
#include "STC/ALL.h"
#include <unordered_map>
#define RETURN(VAR) do {_ret = VAR;return;} while (0)

namespace STC {
    void Generator::visitInteger(AST::Integer* that) {
        RETURN(new PushInteger(that->str));
    }

    void Generator::visitDouble(AST::Double* that) {
        RETURN(new PushDouble(that->str));
    }

    void Generator::visitString(AST::String* that) {
        RETURN(new PushString(that->str));
    }

    void Generator::visitProgram(AST::Program* that) {
        STCList ret;
        for (auto stmt : that->stmts)
            ret.Append(visitX(stmt));
        RETURN(ret);
    }

    void Generator::visitSimpleStmt(AST::SimpleStmt* that) {
        RETURN(visitX(that->expr).Append(new Pop()));
    }

    void Generator::visitForStmt(AST::ForStmt* that) {
        STCList ret;
        STC* end = new Pop();
        STC* o_break = _break;
        _break = end;
        //top=set.__iter__
        ret.Append(visitX(that->set));
        ret.Append(new GetAttr("__iter__"));
        ret.Append(new Call(0));
        //TestNotEND
        STC* loopBeg = new CopyTop();
        ret.Append(loopBeg);
        ret.Append(new GetAttr("__isEnd__"));
        ret.Append(new Call(0));
        ret.Append(new TrueGoto(end));
        //Assign to loop
        ret.Append(new CopyTop);
        ret.Append(new GetAttr("__getElement__"));
        ret.Append(new Call(0));
        ret.Append(visitX(that->var, LValue));
        ret.Append(visitX(that->loop));
        //Get Next
        ret.Append(new GetAttr("__next__"));
        ret.Append(new Call(0));
        ret.Append(new Goto(loopBeg));
        ret.Append(end);
        _break = o_break;
        RETURN(ret);
    }

    void Generator::visitWhileStmt(AST::WhileStmt* that) {
        STCList ret;
        STC* end = new Nop;
        STC* o_break = _break;
        _break = end;
        ret.Append(visitX(that->condition));
        ret.Append(new FalseGoto(end));
        ret.Append(visitX(that->loop));
        ret.Append(new Goto(ret.beg));
        ret.Append(end);
        _break = o_break;
        RETURN(ret);
    }

    void Generator::visitIfStmt(AST::IfStmt* that) {
        STCList ret;
        ret.Append(visitX(that->condition));
        STC* end = new Nop;
        if (that->no) {
            STCList yes = visitX(that->yes);
            STCList no = visitX(that->no);
            ret.Append(new FalseGoto(no.beg));
            ret.Append(yes);
            ret.Append(new Goto(end));
            ret.Append(no);
            ret.Append(end);
        } else {
            ret.Append(new FalseGoto(end));
            ret.Append(visitX(that->yes));
            ret.Append(end);
        }
        RETURN(ret);
    }

    void Generator::visitStmtBlock(AST::StmtBlock* that) {
        STCList ret;
        for (auto stmt : that->stmts)
            ret.Append(visitX(stmt));
        RETURN(ret);
    }
    void Generator::visitBreakStmt(AST::BreakStmt* that) {
        if (_break == 0) {
            //TODO: ADD A Exception For Noncotrolled break.
        } else {
            RETURN(new Goto(_break));
        }
    }

    void Generator::visitReturnStmt(AST::ReturnStmt* that) {
        STCList ret;
        if (that->expr) {
            ret.Append(visitX(that->expr));
        } else {
            //TODO: Push A null.
            ret.Append(new PushInteger("0"));
        }
        ret.Append(new Return());
        RETURN(ret);
    }

    void Generator::visitListExpr(AST::ListExpr* that) {
        STCList ret;
        for (int i = that->exprs.size() - 1; i >= 0; i--)
            ret.Append(visitX(that->exprs[i]));
        ret.Append(new MakeList(that->exprs.size()));
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
        ret.Append(new DefFunc(visitX(that->stmts).beg));
        _break = o_break;
        for (int i = that->funcs.size() - 1; i >= 0; i--) {
            ret.Append(new CopyTop);
            ret.Append(visitX(that->funcs[i], LValue));
        }
        RETURN(ret);
    }

    void Generator::visitStateDef(AST::StateDef* that) {
        STCList ret;
        STC* o_break = _break;
        _break = 0;
        ret.Append(new DefState(visitX(that->stmts).beg));
        _break = o_break;
        for (int i = that->states.size() - 1; i >= 0; i--) {
            ret.Append(new CopyTop);
            ret.Append(visitX(that->states[i], LValue));
        }
        RETURN(ret);
    }

    void Generator::visitGlobalExpr(AST::GlobalExpr* that) {
        RETURN(new PushGlobal());
    }

    void Generator::visitLocaleExpr(AST::LocaleExpr* that) {
        RETURN(new PushLocale());
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
            ret.Append(new CopyTop);
            ret.Append(visitX(that->expr1, LValue));
        } else {
            ret.Append(visitX(that->expr1));
            ret.Append(new GetAttr("__" + DBOperTrans[that->oper] + "__"));
            ret.Append(new Call(1));
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
        ret.Append(new GetAttr("__" + SGOperTrans[that->oper] + "__"));
        ret.Append(new Call(0));
        RETURN(ret);
    }

    void Generator::visitVarLValue(AST::VarLValue* that) {
        STCList ret;
        if (_mode == LValue) {
            ret.Append(visitX(that->obj));
            ret.Append(new SetAttr(that->attr));
        } else {
            ret.Append(visitX(that->obj));
            ret.Append(new GetAttr(that->attr));
        }
        RETURN(ret);
    }

    void Generator::visitArrayAtLValue(AST::ArrayAtLValue* that) {
        STCList ret;
        if (_mode == LValue) {
            ret.Append(visitX(that->index));
            ret.Append(visitX(that->array));
            ret.Append(new GetAttr("__set_element__"));
            ret.Append(new Call(2));
        } else {
            ret.Append(visitX(that->index));
            ret.Append(visitX(that->array));
            ret.Append(new GetAttr("__get_element__"));
            ret.Append(new Call(1));
        }
    }
}
