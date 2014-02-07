#ifndef ST_8329102910_BASETYPE_FUNC
#define ST_8329102910_BASETYPE_FUNC
#include "Object.h"
#include "Runtime/VM.h"
#include <vector>

namespace BaseType {
    class Func : public Object {
    public:
        static pObject STATE;
        Func(const pObject& state = STATE) : Object(std::move(state)) {setAttr("__exec__", this);}
        virtual void run(Runtime::VM& vm, int num) = 0;
    };
}

#endif
