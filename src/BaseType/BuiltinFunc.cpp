#include "BaseType/BuiltinFunc.h"

namespace BaseType {
    void BuiltinFunc::run(Runtime::VM& vm, int num) {
        std::vector<ObjPtr> argsInner;
        std::vector<Object*> args;
        for (int i = 0; i < num; i++) {
            argsInner.push_back(vm.PopObject());
            args.push_back(argsInner[i]);
        }
        Object* ret = func(args);
        vm.PushObject(ret);
    }
}
