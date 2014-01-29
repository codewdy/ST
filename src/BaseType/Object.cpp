#include "BaseType/Object.h"

namespace BaseType {
    Object::Object(Object* state) {
       setAttr("__state__", state);
    }

    Object* Object::_getAttr(std::string attr) {
        Object* ret = 0;
        auto tmp = dict.find(attr);
        if (tmp == dict.end()) {
            for (Object* st = dict["__state__"]; ; st = st->dict["__dict__"]) {
                auto t = st->dict.find(attr);
                if (t != st->dict.end()) {
                    ret = t->second;
                    break;
                }
                if (st == StateObject)
                    break;
            }
        } else
            ret = tmp->second;
        if (ret->_getAttr("__exec__"))
            return 0;
        else
            return ret;
        return 0;
    }

    void Object::_setAttr(std::string attr, Object* obj) {
        dict[attr] = ObjPtr(obj, this);
    }

    Object::~Object() {
    }
}
