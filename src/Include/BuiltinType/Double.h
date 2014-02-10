#ifndef ST_1782936781_BUILTINTYPE_DOUBLE
#define ST_1782936781_BUILTINTYPE_DOUBLE
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/BuiltinFunc.h"

namespace BuiltinType {
    namespace Double {
        typedef double Inner;
        extern pObject STATE;
        void InitState();
        pObject Create(const std::string& str);
        pObject Create(Inner num);
    }
}
#endif
