#include "STC/STC.h"

namespace STC {
    std::unordered_map<int, STC::Arg> STC::ArgMap = {
#define ST_NONEARG(CLASS) {STC::CLASS, STC::NoneArg},
#define ST_STRINGARG(CLASS) {STC::CLASS, STC::StringArg},
#define ST_INTARG(CLASS) {STC::CLASS, STC::IntArg},
#define ST_GOTOARG(CLASS) {STC::CLASS, STC::GotoArg},
#define ST_BLOCKARG(CLASS) {STC::CLASS, STC::BlockArg},
        ST_ALL_STC_DEF
#undef ST_NONEARG
#undef ST_STRINGARG
#undef ST_INTARG
#undef ST_GOTOARG
#undef ST_BLOCKARG
    };
}
