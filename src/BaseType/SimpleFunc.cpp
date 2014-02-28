#include "BaseType/SimpleFunc.h"
#include "BaseType/Namespace.h"
#include "BaseType/Excpt.h"

namespace BaseType {
    void SimpleFunc::run(Runtime::VM& vm, int num) {
        if (argsName.size() != num) {
            ST_RAISE(VM, {{"__state__", Excpt::ArgCountError}});
        }
        pObject locale = new BaseType::Namespace(getAttr("__locale__"));
        for (int i = 0; i < num; i++)
            locale->Object::_setAttr(argsName[i], vm.PopObject().GetPtr());
        vm.PushContext(Runtime::Context(getAttr("__global__"), locale, stc));
    }
}
