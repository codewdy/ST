#include "BaseType/State.h"
#include "BaseType/Excpt.h"
#include <iostream>

namespace BaseType {
    Object* State::_getAttr(const std::string& attr) {
        Object* ret = Object::_getAttr(attr);
        if (ret)
            return ret;
        Object* base = dict["__base__"].GetPtr();
        while (true) {
            if (base->dict.find(attr) != base->dict.end())
                return base->dict[attr].GetPtr();
            if (base == Object::STATE.GetPtr())
                break;
            base = base->dict["__base__"].GetPtr();
        }
        return nullptr;
    }
    void State::run(Runtime::VM& vm, int num) {
        vm.PushObject(new Object(this));
        std::cout << "123" << std::endl;
        Object *init = this->_getAttr("__init__");
        if (init) {
            vm.PushObject(init);
            vm.Call(num + 1);
        } else {
            if (num) {
                ST_RAISE(VM, {{"__state__", Excpt::ArgCountError}});
            }
        }
    }
}
