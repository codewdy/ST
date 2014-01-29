#include "BaseType/SimpleFunc.h"

namespace BaseType {
    void SimpleFunc::run(Runtime::VM& vm, int num) {
        if (argsName.size() != num) {
            //TODO: Add An Exception.
        }
        //TODO: Add a state about locale.
        vm.PushContext(Runtime::Context(getAttr("__global__"), new Object, stc));
        for (int i = 0; i < num; i++)
            vm.TopContext().Locale->setAttr(argsName[i], vm.PopObject());
    }
}
