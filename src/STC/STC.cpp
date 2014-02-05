#include "STC/STC.h"

namespace STC {
    std::unordered_map<int, STC::Arg> STC::ArgMap = {
#define NONEARG(CLASS) {STC::CLASS, STC::NoneArg},
#define STRINGARG(CLASS) {STC::CLASS, STC::StringArg},
#define INTARG(CLASS) {STC::CLASS, STC::IntArg},
#define GOTOARG(CLASS) {STC::CLASS, STC::GotoArg},
#define BLOCKARG(CLASS) {STC::CLASS, STC::BlockArg},
        ALL_STC_DEF
#undef NONEARG
#undef STRINGARG
#undef INTARG
#undef GOTOARG
#undef BLOCKARG
    };
}
