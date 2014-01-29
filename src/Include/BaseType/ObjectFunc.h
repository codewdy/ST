#ifndef ST_1238743298_BASETYPE_OBJECTFUNC
#define ST_1238743298_BASETYPE_OBJECTFUNC
#include "Func.h"

namespace BaseType {
    class ObjectFunc : public Func {
    public:
        static ObjPtr STATE;
        ObjectFunc(Object* obj, Object* func) : Func(STATE) {setAttr("__obj__", obj); setAttr("__func__", func);}
        virtual void run(Runtime::VM& vm, int num);
    };
}

#endif
