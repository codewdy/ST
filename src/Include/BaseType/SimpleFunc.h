#ifndef ST_8917231287_BASETYPE_SIMPLEFUNC
#define ST_8917231287_BASETYPE_SIMPLEFUNC
#include "Func.h"
#include "STC/STC.h"

namespace BaseType {
    class SimpleFunc : public Func {
    public:
        static ObjPtr STATE;
        STC::STC* stc;
        std::vector<std::string> argsName;
        SimpleFunc(Object* Global, STC::STC* _stc) : Func(STATE), stc(_stc) {setAttr("__global__", Global);}
        virtual void run(Runtime::VM& vm, int num);
    };
}
#endif
