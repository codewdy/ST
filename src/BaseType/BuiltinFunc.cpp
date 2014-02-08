#include "BaseType/BuiltinFunc.h"

namespace BaseType {
    void BuiltinFunc::run(Runtime::VM& vm, int num) {
        std::vector<pObject> args;
        for (int i = 0; i < num; i++)
            args.push_back(std::move(vm.PopObject()));
        pObject ret = func(std::move(args));
        vm.PushObject(std::move(ret));
    }
}
