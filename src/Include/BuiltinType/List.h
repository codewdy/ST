#ifndef ST_2131256523_BUILTINTYPE_LIST
#define ST_2131256523_BUILTINTYPE_LIST
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"
#include <vector>

namespace BuiltinType {
    namespace List {
        typedef std::vector<BaseType::ObjPtr> Inner;
        DEF_BUILTIN_FUNC(__add__);
        DEF_BUILTIN_FUNC(__mul__);
        DEF_BUILTIN_FUNC(__str__);
        extern BaseType::ObjPtr STATE;
        void InitState();
        BaseType::Object* Create(Inner& vars);
    }
}
#endif
