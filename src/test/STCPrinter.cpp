#include "STCPrinter.h"
#include "STC/ALL.h"

void STCPrinter(STC::STC* lst, std::ostream& out, std::string prefix) {
    for (; lst; lst = lst->next) {
        out << '[' << lst << ']' << prefix;
        switch (lst->type) {
#define PRINTTYPE(CLASS) case STC::STC::CLASS: out << #CLASS;break;
            PRINTTYPE(CopyTop)
            PRINTTYPE(PushLocale)
            PRINTTYPE(PushGlobal)
            PRINTTYPE(PushNull)
            PRINTTYPE(PushString)
            PRINTTYPE(PushInteger)
            PRINTTYPE(PushDouble)
            PRINTTYPE(GetAttr)
            PRINTTYPE(SetAttr)
            PRINTTYPE(Goto)
            PRINTTYPE(TrueGoto)
            PRINTTYPE(FalseGoto)
            PRINTTYPE(Call)
            PRINTTYPE(Return)
            PRINTTYPE(MakeList)
            PRINTTYPE(DefFunc)
            PRINTTYPE(DefState)
            PRINTTYPE(Pop)
            PRINTTYPE(Nop)
            default:
                break;
        }
        switch (lst->arg) {
            case STC::STC::NoneArg:
                break;
            case STC::STC::StringArg:
                out << "[" << lst->str << "]";
                break;
            case STC::STC::IntArg:
                out << "[" << lst->num << "]";
                break;
            case STC::STC::GotoArg:
                out << "[" << lst->code << "]";
                break;
            case STC::STC::BlockArg:
                out << "[" << lst->code << "]";
                break;
        }
        out << std::endl;
        if (lst->arg == STC::STC::BlockArg)
            STCPrinter(lst->code, out, prefix + "    ");
    }
}

