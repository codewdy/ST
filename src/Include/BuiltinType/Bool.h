#ifndef ST_1237615237_BUILTINTYPE_BOOL
#define ST_1237615237_BUILTINTYPE_BOOL
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"

namespace BuiltinType {
    namespace Bool {
        typedef bool Inner;
        DEF_BUILTIN_FUNC(__and__);
        DEF_BUILTIN_FUNC(__or__);
        DEF_BUILTIN_FUNC(__not__);
        DEF_BUILTIN_FUNC(__str__);
        extern pObject STATE, TRUE, FALSE;
        void InitState();
        pObject Create(Inner num);
    }
}
#endif

