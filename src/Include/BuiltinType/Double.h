#ifndef ST_1782936781_BUILTINTYPE_DOUBLE
#define ST_1782936781_BUILTINTYPE_DOUBLE
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"

namespace BuiltinType {
    namespace Double {
        typedef double Inner;
        DEF_BUILTIN_FUNC(__add__);
        DEF_BUILTIN_FUNC(__minus__);
        DEF_BUILTIN_FUNC(__mul__);
        DEF_BUILTIN_FUNC(__div__);
        DEF_BUILTIN_FUNC(__str__);
        extern BaseType::ObjPtr STATE;
        void InitState();
        BaseType::Object* Create(std::string str);
        BaseType::Object* Create(Inner num);
    }
}
#endif
