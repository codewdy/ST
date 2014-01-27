#ifndef ST_7823912731_BASETYPE_BUILTINFUNC
#define ST_7823912731_BASETYPE_BUILTINFUNC

#include "Func.h"

namespace BaseType {
    class BuiltinFunc : public Func {
    public:
        typedef pObject pFunc(const std::vector<pObject>&);
        pFunc func;
        virtual pObject run(std::vector<pObject>);
        BuiltinFunc(pFunc _func);
    };
}

#endif
