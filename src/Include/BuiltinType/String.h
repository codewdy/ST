#ifndef ST_1826387964_BUILTINTYPE_STRING
#define ST_1826387964_BUILTINTYPE_STRING
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"
#include <string>

namespace BuiltinType {
    namespace String {
        typedef std::string Inner;
        DEF_BUILTIN_FUNC(__add__);
        DEF_BUILTIN_FUNC(__mul__);
        DEF_BUILTIN_FUNC(__str__);
        extern BaseType::ObjPtr STATE;
        void InitState();
        BaseType::Object* Create(Inner str);
    }
}
#endif
