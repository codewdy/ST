#include "BaseType/Object.h"
#include "BaseType/ObjectFunc.h"
#include "BaseType/SimpleFunc.h"
#include "BaseType/BuiltinFunc.h"
#include "ToolKit.h"
#include <iostream>

namespace BaseType {
    Object::Object(const pObject& state) {
        dict["__state__"] = pObjectExt(state.GetPtr(), this);
    }

    Object* Object::_getAttr(const std::string& attr) {
        Object* ret = 0;
        auto tmp = dict.find(attr);
        if (tmp == dict.end()) {
            for (Object* st = dict["__state__"].GetPtr(); st; st = st->dict["__base__"].GetPtr()) {
                auto t = st->dict.find(attr);
                if (t != st->dict.end()) {
                    ret = t->second.GetPtr();
                    break;
                }
            }
        } else
            return tmp->second.GetPtr();
        if (!ret)
            return 0;
        Object* state = ret->dict["__state__"].GetPtr();
        if (BuiltinFunc::STATE.ref_equal(state) || SimpleFunc::STATE.ref_equal(state))
            return new ObjectFunc(this, ret);
        else
            return ret;
    }

    void Object::_setAttr(const std::string& attr, Object* obj) {
        dict[attr] = pObjectExt(obj, this);
    }

    Object::~Object() {
    }
}
