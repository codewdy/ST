#include "BaseType/Object.h"

namespace BaseType {
    Object::Object(Object* state) {
        setAttr("__state__", state);
    }

    Object* Object::getAttr(std::string attr) {
        auto tmp = dict.find(attr);
        if (tmp == dict.end())
            return getAttr("__state__")->getAttr(attr);
        else
            return tmp->second;
    }

    void Object::setAttr(std::string attr, Object* obj) {
        dict[attr] = obj;
    }

    Object::~Object() {
    }
}
