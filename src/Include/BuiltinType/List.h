#ifndef ST_2131256523_BUILTINTYPE_LIST
#define ST_2131256523_BUILTINTYPE_LIST
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"
#include <vector>

namespace BuiltinType {
    namespace List {
        typedef std::vector<pObjectExt> Inner;
        typedef std::vector<pObject> InitInner;
        DEF_BUILTIN_FUNC(__add__);
        DEF_BUILTIN_FUNC(__mul__);
        DEF_BUILTIN_FUNC(__str__);
        DEF_BUILTIN_FUNC(__get_element__);
        DEF_BUILTIN_FUNC(__iter__);
        DEF_BUILTIN_FUNC(Iter__next__);
        DEF_BUILTIN_FUNC(Iter__is_end__);
        DEF_BUILTIN_FUNC(Iter__get__);
        extern pObject STATE, IterSTATE;
        void InitState();
        pObject Create(const InitInner& vars);
    }
}
#endif
