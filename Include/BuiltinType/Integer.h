#ifndef ST_9187239119_BUILTINTYPE_INTEGER
#define ST_9187239119_BUILTINTYPE_INTEGER
#include "../BaseType/Object.h"
#include "../BaseType/State.h"
#include "../BaseType/BuiltinFunc.h"

namespace BuiltinType {
    namespace Integer {
        typedef int Inner;
        extern pObject STATE;
        void InitState();
        pObject Create(const std::string& str);
        pObject Create(Inner num);
    }
}
#endif
