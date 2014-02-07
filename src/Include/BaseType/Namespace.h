#ifndef ST_1896731236_BASETYPE_NAMESPACE
#define ST_1896731236_BASETYPE_NAMESPACE

#include "Object.h"

namespace BaseType {
    class Namespace : public Object {
    public:
        static pObject STATE;
        virtual Object* _getAttr(const std::string& attr);
        virtual void _setAttr(const std::string& attr, Object* obj);
        virtual bool setAttrIfHas(const std::string& attr, Object* obj);
        Namespace(const pObject& Parent = 0) : Object(STATE) {
            if (Parent && Parent->dict["__state__"] != Namespace::STATE)
                Object::_setAttr("__parent__", Parent->dict["__parent__"]);
            else
                Object::_setAttr("__parent__", Parent);
        }
    };

    class ObjectNamespace : public Namespace {
    public:
        static pObject STATE;
        virtual Object* _getAttr(const std::string& attr);
        virtual void _setAttr(const std::string& attr, Object* obj);
        virtual bool setAttrIfHas(const std::string& attr, Object* obj);
        ObjectNamespace(const pObject& Parent, const pObject& Inner) : Namespace(Parent) {Object::_setAttr("__inner__", Inner);}
    };
}
#endif
