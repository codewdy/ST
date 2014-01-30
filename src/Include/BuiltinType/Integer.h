#ifndef ST_9187239119_BUILTINTYPE_INTEGER
#define ST_9187239119_BUILTINTYPE_INTEGER
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"

namespace BuiltinObject {
    namespace Integer {
        typedef int IntegerInner;
        DEF_BUILTIN_FUNC(__add__);
        DEF_BUILTIN_FUNC(__minus__);
        DEF_BUILTIN_FUNC(__mul__);
        DEF_BUILTIN_FUNC(__div__);
        DEF_BUILTIN_FUNC(__mod__);
        extern BaseType::State STATE;
        void InitState();
        BaseType::Object* Create(std::string str);
        BaseType::Object* Create(IntegerInner num);
    }
}
#endif
