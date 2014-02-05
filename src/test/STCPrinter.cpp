#include "STCPrinter.h"
#include "STC/ALL.h"

void STCPrinter(STC::STC* lst, std::ostream& out, std::string prefix) {
    for (; lst; lst = lst->next) {
        out << '[' << lst << ']' << prefix;
        switch (lst->type) {
#define NONEARG(CLASS) case STC::STC::CLASS: out << #CLASS << std::endl;break;
#define INTARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->num << "]" << std::endl;break;
#define STRINGARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->str << "]" << std::endl;break;
#define GOTOARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->code << "]" << std::endl;break;
#define BLOCKARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->code << "]" << std::endl;STCPrinter(lst->code, out, prefix + "    ");break;
            ALL_STC_DEF
#undef NONEARG
#undef INTARG
#undef STRINGARG
#undef GOTOARG
#undef BLOCKARG
            default:
                break;
        }
    }
}

