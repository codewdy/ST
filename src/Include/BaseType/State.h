#ifndef ST_8937289123_BASETYPE_STATE
#define ST_8937289123_BASETYPE_STATE

#include "Object.h"

namespace BaseType {
    class State : public Object {
    public:
        static ObjPtr STATE;
        State(Object* base = Object::STATE) : Object(STATE) {setAttr("__base__", base);}
        virtual Object* _getAttr(std::string attr);
    };
}
#endif
