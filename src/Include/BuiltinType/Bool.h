#ifndef ST_1237615237_BUILTINTYPE_BOOL
#define ST_1237615237_BUILTINTYPE_BOOL
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"

namespace BuiltinType {
    namespace Bool {
        typedef bool Inner;
        extern pObject STATE, TRUE, FALSE;
        void InitState();
        pObject Create(Inner num);
    }
}
#endif

