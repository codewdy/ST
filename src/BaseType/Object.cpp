#include "BaseType/Object.h"
#include "BaseType/ObjectFunc.h"
#include <iostream>

namespace BaseType {
    Object::Object(Object* state) {
       setAttr("__state__", state);
    }

    Object* Object::_getAttr(std::string attr) {
        Object* ret = 0;
        auto tmp = dict.find(attr);
        if (tmp == dict.end()) {
            for (Object* st = dict["__state__"]; ; st = st->dict["__base__"]) {
                auto t = st->dict.find(attr);
                if (t != st->dict.end()) {
                    ret = t->second;
                    break;
                }
                if (st == Object::STATE)
                    break;
            }
        } else
            return tmp->second;
        if (!ret)
            return 0;
        if (attr == "__exec__")
            return ret;
        if (ret->_getAttr("__exec__"))
            return new ObjectFunc(this, ret);
        else
            return ret;
    }

    void Object::_setAttr(std::string attr, Object* obj) {
        dict[attr] = ObjPtr(obj, this);
    }

    Object::~Object() {
    }
}
