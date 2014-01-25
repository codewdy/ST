#include "STC/STC.h"

namespace STC {
    std::unordered_map<int, STC::Arg> STC::ArgMap = {
        {STC::CopyTop, STC::NoneArg},
        {STC::PushLocale, STC::NoneArg},
        {STC::PushGlobal, STC::NoneArg},
        {STC::PushNull, STC::NoneArg},
        {STC::PushString, STC::StringArg},
        {STC::PushInteger, STC::StringArg},
        {STC::PushDouble, STC::StringArg},
        {STC::GetAttr, STC::StringArg},
        {STC::SetAttr, STC::StringArg},
        {STC::Goto, STC::GotoArg},
        {STC::TrueGoto, STC::GotoArg},
        {STC::FalseGoto, STC::GotoArg},
        {STC::Call, STC::IntArg},
        {STC::Return, STC::NoneArg},
        {STC::MakeList, STC::IntArg},
        {STC::DefFunc, STC::BlockArg},
        {STC::DefState, STC::BlockArg},
        {STC::Pop, STC::NoneArg},
        {STC::Nop, STC::NoneArg},
    };
}
