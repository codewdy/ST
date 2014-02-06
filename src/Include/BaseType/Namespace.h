#ifndef ST_1896731236_BASETYPE_NAMESPACE
#define ST_1896731236_BASETYPE_NAMESPACE

#include "Object.h"

namespace BaseType {
    class Namespace : public Object {
    public:
        static ObjPtr STATE;
        virtual Object* _getAttr(std::string attr);
        virtual void _setAttr(std::string attr, Object* obj);
        virtual bool setAttrIfHas(std::string attr, Object* obj);
        Namespace(Object* Parent = 0) : Object(STATE) {dict["__parent__"] = Parent;}
    };

    class ObjectNamespace : public Namespace {
    public:
        static ObjPtr STATE;
        virtual Object* _getAttr(std::string attr);
        virtual void _setAttr(std::string attr, Object* obj);
        virtual bool setAttrIfHas(std::string attr, Object* obj);
        ObjectNamespace(Object* Parent, Object* Inner) : Namespace(Parent) {dict["__inner__"] = Inner;}
    };
}
#endif
