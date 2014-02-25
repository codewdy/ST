#ifndef ST_2131256523_BUILTINTYPE_LIST
#define ST_2131256523_BUILTINTYPE_LIST
#include "../BaseType/Object.h"
#include "../BaseType/State.h"
#include "../BaseType/BuiltinFunc.h"
#include <vector>

namespace BuiltinType {
    namespace List {
        typedef std::vector<pObjectExt> Inner;
        typedef std::vector<pObject> InitInner;
        extern pObject STATE, IterSTATE;
        void InitState();
        pObject Create(const InitInner& vars);
    }
}
#endif
