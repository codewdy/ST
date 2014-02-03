#include "BaseType/Namespace.h"

namespace BaseType {
    Object* Namespace::_getAttr(std::string attr) {
        Object* that = this;
        while (that) {
            if (that->dict.find(attr) != that->dict.end())
                return that->dict[attr];
        }
        return 0;
    }

    Object* ObjectNamespace::_getAttr(std::string attr) {
        Object* ret = dict["__inner__"]->_getAttr(attr);
        if (ret)
            return ret;
        Object* that = this;
        while (that) {
            if (that->dict.find(attr) != that->dict.end())
                return that->dict[attr];
        }
        return 0;
    }

    void ObjectNamespace::_setAttr(std::string attr, Object* obj) {
        dict["__inner__"]->_setAttr(attr, obj);
    }
}
