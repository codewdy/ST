#include "BaseType/SimpleFunc.h"
#include "BaseType/Namespace.h"
#include "BaseType/Excpt.h"

namespace BaseType {
    void SimpleFunc::run(Runtime::VM& vm, int num) {
        if (argsName.size() != num) {
            ST_RAISE(VM, {{"__state__", Excpt::ArgCountError}});
        }
        vm.PushContext(Runtime::Context(getAttr("__global__"), new BaseType::Namespace(getAttr("__locale__")), stc));
        pObject loc = vm.TopContext().Locale;
        for (int i = 0; i < num; i++)
            loc->Object::_setAttr(argsName[i], vm.PopObject().GetPtr());
        vm.TopContext().ObjSize -= num - 1;
    }
}
