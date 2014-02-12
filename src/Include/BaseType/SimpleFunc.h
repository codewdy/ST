#ifndef ST_8917231287_BASETYPE_SIMPLEFUNC
#define ST_8917231287_BASETYPE_SIMPLEFUNC
#include "Func.h"
#include "../STC/STC.h"

namespace BaseType {
    class SimpleFunc : public Func {
    public:
        static pObject STATE;
        STC::STC* stc;
        std::vector<std::string> argsName;
        SimpleFunc(const pObject& Global, const pObject& Locale, STC::STC* _stc) : Func(STATE), stc(_stc) {setAttr("__global__", Global);setAttr("__locale__", Locale);}
        virtual void run(Runtime::VM& vm, int num);
    };
}
#endif
