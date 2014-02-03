#include "BuiltinType/Init.h"
#include "BuiltinType/Integer.h"

namespace BuiltinType {
    void InitState() {
        Integer::InitState();
    }

    void Init(BaseType::Object* obj) {
        obj->setAttr("Integer", Integer::STATE);
    }
}
