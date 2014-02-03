#include "BaseType/BuiltinFunc.h"

namespace BaseType {
    void BuiltinFunc::run(Runtime::VM& vm, int num) {
        std::vector<Object*> args;
        for (int i = 0; i < num; i++)
            args.push_back(vm.PopObject());
        Object* ret = func(args);
        vm.PushObject(ret);
    }
}
