#include "STCPrinter.h"
#include "STC/ALL.h"

void STCPrinter(STC::STC* lst, std::ostream& out, std::string prefix) {
    for (; lst; lst = lst->next) {
        out << prefix;
        switch (lst->type) {
#define SimpleOutput(CLASS) case STC::STC::CLASS: out << lst << "\t" << #CLASS; break;
            SimpleOutput(CopyTop)
            SimpleOutput(PushLocale)
            SimpleOutput(PushGlobal)
            SimpleOutput(Return)
            SimpleOutput(Nop)
            SimpleOutput(Pop)
#define AttrOutput(CLASS,ATTR) case STC::STC::CLASS: out << lst << "\t" << #CLASS <<"[" << ((STC::CLASS*)lst)->ATTR << "]"; break;
            AttrOutput(PushString, str)
            AttrOutput(PushInteger, str)
            AttrOutput(PushDouble, str)
            AttrOutput(GetAttr, str)
            AttrOutput(SetAttr, str)
            AttrOutput(Goto, code)
            AttrOutput(TrueGoto, code)
            AttrOutput(FalseGoto, code)
            AttrOutput(Call, parmCount)
            AttrOutput(MakeList, num)
#define RecurOutput(CLASS,ATTR) case STC::STC::CLASS: out << lst << "\t" << #CLASS <<"[" << ((STC::CLASS*)lst)->ATTR << "]:";\
    STCPrinter(((STC::CLASS*)lst)->ATTR, out, "    " + prefix); break;
            RecurOutput(DefFunc, code)
            RecurOutput(DefState, code)
        }
        out << std::endl;
    }
}

