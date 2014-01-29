#ifndef ST_1896731236_BASETYPE_NAMESPACE
#define ST_1896731236_BASETYPE_NAMESPACE

#include "Object.h"

namespace BaseType {
    class Namespace : public Object {
    public:
        static ObjPtr STATE;
        virtual Object* _getAttr(std::string attr);
        Namespace(Object* Parent) : Object(STATE) {setAttr("__parent__", Parent);}
    };

    class ObjectNamespace : public Object {
    public:
        static ObjPtr STATE;
        virtual Object* _getAttr(std::string attr);
        virtual void _setAttr(std::string attr, Object* obj);
        ObjectNamespace(Object* Parent, Object* Inner) : Object(STATE) {setAttr("__parent__", Parent); setAttr("__inner__", Inner);}
    };
}
#endif
