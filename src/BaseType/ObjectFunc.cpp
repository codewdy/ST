#include "BaseType/ObjectFunc.h"

namespace BaseType {
    void ObjectFunc::run(Runtime::VM& vm, int num) {
        vm.PushObject(getAttr("__obj__"));
        vm.PushObject(getAttr("__func__"));
        vm.Call(num + 1);
    }
}
