#include "BaseType/Namespace.h"
#include "ToolKit.h"
#include <iostream>

namespace BaseType {
    Object* Namespace::_getAttr(const std::string& attr) {
        Object* that = this;
        while (that) {
            if (that->dict.find(attr) != that->dict.end())
                return that->dict[attr];
            that = that->dict["__parent__"];
        }
        return 0;
    }

    void Namespace::_setAttr(const std::string& attr, Object* obj) {
        if (!this->setAttrIfHas(attr, obj))
            Object::_setAttr(attr, obj);
    }

    bool Namespace::setAttrIfHas(const std::string& attr, Object* obj) {
        if (dict.find(attr) != dict.end()) {
            Object::_setAttr(attr, obj);
            return true;
        } else if (dict["__parent__"] != nullptr) {
            Namespace* parent = ToolKit::SafeConvert<Namespace>(dict["__parent__"]);
            return parent->setAttrIfHas(attr, obj);
        } else
            return false;
    }

    Object* ObjectNamespace::_getAttr(const std::string& attr) {
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

    void ObjectNamespace::_setAttr(const std::string& attr, Object* obj) {
        if (!this->setAttrIfHas(attr, obj))
            dict["__inner__"]->_setAttr(attr, obj);
    }

    bool ObjectNamespace::setAttrIfHas(const std::string& attr, Object* obj) {
        if (dict["__inner__"]->dict.find(attr) != dict.end()) {
            dict[attr]->setAttr(attr, obj);
            return true;
        } else if (dict["__parent__"] != nullptr) {
            Namespace* parent = ToolKit::SafeConvert<Namespace>(dict["__parent__"]);
            return parent->setAttrIfHas(attr, obj);
        } else
            return false;
    }
}
