#include "BaseType/State.h"

namespace BaseType {
    Object* State::_getAttr(std::string attr) {
        Object* ret = Object::_getAttr(attr);
        if (ret)
            return ret;
        Object* base = dict["__base__"];
        while (true) {
            if (base->dict.find(attr) != base->dict.end())
                return base->dict[attr];
            if (base == StateObject)
                break;
            base = base->dict["__base__"];
        }
        return 0;
    }
}
