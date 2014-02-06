#include "BaseType/Object.h"
#include "BaseType/ObjectFunc.h"
#include "BaseType/SimpleFunc.h"
#include "BaseType/BuiltinFunc.h"
#include "ToolKit.h"
#include <iostream>

namespace BaseType {
    Object::Object(Object* state) {
        dict["__state__"] = ObjPtr(state, this);
    }

    Object* Object::_getAttr(std::string attr) {
        Object* ret = 0;
        auto tmp = dict.find(attr);
        if (tmp == dict.end()) {
            for (Object* st = dict["__state__"]; st; st = st->dict["__base__"]) {
                auto t = st->dict.find(attr);
                if (t != st->dict.end()) {
                    ret = t->second;
                    break;
                }
            }
        } else
            return tmp->second;
        if (!ret)
            return 0;
        Object* state = ret->dict["__state__"];
        if (state == BuiltinFunc::STATE || state == SimpleFunc::STATE)
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
