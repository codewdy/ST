#include "STCPrinter.h"
#include "STC/ALL.h"

void STCPrinter(STC::STC* lst, std::ostream& out, std::string prefix) {
    for (; lst; lst = lst->next) {
        out << '[' << lst << ']' << prefix;
        switch (lst->type) {
#define ST_NONEARG(CLASS) case STC::STC::CLASS: out << #CLASS << std::endl;break;
#define ST_INTARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->num << "]" << std::endl;break;
#define ST_STRINGARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->str << "]" << std::endl;break;
#define ST_GOTOARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->code << "]" << std::endl;break;
#define ST_BLOCKARG(CLASS) case STC::STC::CLASS: out << #CLASS << "["<< lst->code << "]" << std::endl;STCPrinter(lst->code, out, prefix + "    ");break;
            ST_ALL_STC_DEF
#undef ST_NONEARG
#undef ST_INTARG
#undef ST_STRINGARG
#undef ST_GOTOARG
#undef ST_BLOCKARG
            default:
                break;
        }
    }
}

