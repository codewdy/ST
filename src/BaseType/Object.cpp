#include "BaseType/Object.h"
#include "BaseType/ObjectFunc.h"
#include "BaseType/SimpleFunc.h"
#include "BaseType/BuiltinFunc.h"
#include "BuiltinType/String.h"
#include "BaseType/Excpt.h"
#include "ToolKit.h"
#include <iostream>

namespace BaseType {
    Object::Object(const pObject& state) {
        dict["__state__"] = pObjectExt(state.GetPtr(), this);
    }

    Object* Object::_getAttr(const std::string& attr) {
        Object* ret = nullptr;
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
            return nullptr;
        Object* state = ret->dict["__state__"].GetPtr();
        if (BuiltinFunc::STATE.ref_equal(state) || SimpleFunc::STATE.ref_equal(state))
            return new ObjectFunc(this, ret);
        else
            return ret;
    }

    void Object::_setAttr(const std::string& attr, Object* obj) {
        dict[attr] = pObjectExt(obj, this);
    }

    pObject Object::getAttr(const std::string& attr) {
        Object* ret = _getAttr(attr);
        if (ret)
            return ret;
        else {
            ST_RAISE(VM, {
                {"__state__", Excpt::AttrNotFound},
                {"obj", this},
                {"attr", BuiltinType::String::Create(attr)},
            });
        }
    }

    void Object::setAttr(const std::string& attr, const pObject& obj) {
        _setAttr(attr, obj.GetPtr());
    }

    Object::~Object() {
    }
}
