#ifndef ST_1826387964_BUILTINTYPE_STRING
#define ST_1826387964_BUILTINTYPE_STRING
#include "../BaseType/Object.h"
#include "../BaseType/State.h"
#include "../BaseType/BuiltinFunc.h"
#include <string>

namespace BuiltinType {
    namespace String {
        typedef std::string Inner;
        extern pObject STATE;
        void InitState();
        pObject Create(const Inner& str);
        pObject Create(Inner&& str);
    }
}
#endif
