#include "AST/ALL.h"
#include "STC/ALL.h"
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
        //top=set.__iter__
        ret.Append(visitX(that->set));
        ret.Append(new GetAttr("__iter__"));
        ret.Append(new Call(0));
        //TestNotEND
        STC* loopBeg = new CopyTop();
        STC* end = new Pop();
        ret.Append(loopBeg);
        ret.Append(new GetAttr("__isEnd__"));
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
        RETURN(ret);
    }

    void Generator::visitWhileStmt(AST::WhileStmt* that) {
        STCList ret;
        STC* end = new Nop;
        ret.Append(visitX(that->condition));
        ret.Append(new FalseGoto(end));
        ret.Append(visitX(that->loop));
        ret.Append(new Goto(ret.beg));
        ret.Append(end);
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
}
