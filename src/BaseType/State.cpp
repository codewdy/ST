#include "BaseType/State.h"
#include <iostream>

namespace BaseType {
    Object* State::_getAttr(std::string attr) {
        Object* ret = Object::_getAttr(attr);
        if (ret)
            return ret;
        Object* base = dict["__base__"];
        while (true) {
            if (base->dict.find(attr) != base->dict.end())
                return base->dict[attr];
            if (base == Object::STATE)
                break;
            base = base->dict["__base__"];
        }
        return 0;
    }
    void State::run(Runtime::VM& vm, int num) {
        vm.PushObject(new Object(this));
        Object *init = this->_getAttr("__init__");
        if (init) {
            vm.PushObject(init);
            vm.Call(num + 1);
        } else {
            if (num) {
                //TODO: Add an Exception.
            }
        }
    }
}
