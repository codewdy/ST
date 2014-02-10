#ifndef ST_7823912731_BASETYPE_BUILTINFUNC
#define ST_7823912731_BASETYPE_BUILTINFUNC

#include "Func.h"
#include <functional>

namespace BaseType {
    class BuiltinFunc : public Func {
    public:
        static pObject STATE;
        //typedef pObject (*pFunc)(const std::vector<pObject>& args);
        typedef std::function<pObject(const std::vector<pObject>&)> pFunc;
        pFunc func;
        virtual void run(Runtime::VM& vm, int num);
        BuiltinFunc(pFunc _func) : Func(STATE), func(_func) {}
    };
#define DEF_BUILTIN_FUNC(FUNC_NAME) pObject FUNC_NAME(const std::vector<pObject>& args)
}

#endif
