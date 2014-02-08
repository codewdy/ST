#include "BuiltinType/Init.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/List.h"
#include "BuiltinType/Bool.h"

namespace BuiltinType {
    void InitState() {
        Integer::InitState();
        Double::InitState();
        String::InitState();
        List::InitState();
        Bool::InitState();
    }

    void Init(const pObject& obj) {
        obj->setAttr("Integer", Integer::STATE);
        obj->setAttr("String", String::STATE);
        obj->setAttr("Double", Double::STATE);
        obj->setAttr("List", List::STATE);
        obj->setAttr("Bool", Bool::STATE);
        obj->setAttr("true", Bool::TRUE);
        obj->setAttr("false", Bool::FALSE);
    }
}
