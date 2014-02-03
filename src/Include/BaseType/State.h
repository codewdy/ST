#ifndef ST_8937289123_BASETYPE_STATE
#define ST_8937289123_BASETYPE_STATE

#include "Func.h"

namespace BaseType {
    class State : public Func {
    public:
        static ObjPtr STATE;
        State(Object* base = Object::STATE) : Func(STATE) {setAttr("__base__", base);}
        virtual Object* _getAttr(std::string attr);
        void run(Runtime::VM& vm, int num);
    };
}
#endif
