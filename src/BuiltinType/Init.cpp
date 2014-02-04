#include "BuiltinType/Init.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/List.h"

namespace BuiltinType {
    void InitState() {
        Integer::InitState();
        Double::InitState();
        String::InitState();
        List::InitState();
    }

    void Init(BaseType::Object* obj) {
        obj->setAttr("Integer", Integer::STATE);
        obj->setAttr("String", String::STATE);
        obj->setAttr("Double", Double::STATE);
        obj->setAttr("List", List::STATE);
    }
}
