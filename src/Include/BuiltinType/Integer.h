#ifndef ST_9187239119_BUILTINTYPE_INTEGER
#define ST_9187239119_BUILTINTYPE_INTEGER
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"

namespace BuiltinType {
    namespace Integer {
        typedef int Inner;
        DEF_BUILTIN_FUNC(__add__);
        DEF_BUILTIN_FUNC(__minus__);
        DEF_BUILTIN_FUNC(__mul__);
        DEF_BUILTIN_FUNC(__div__);
        DEF_BUILTIN_FUNC(__mod__);
        DEF_BUILTIN_FUNC(__str__);
        DEF_BUILTIN_FUNC(__equal__);
        DEF_BUILTIN_FUNC(__less_than__);
        extern pObject STATE;
        void InitState();
        pObject Create(const std::string& str);
        pObject Create(Inner num);
    }
}
#endif
