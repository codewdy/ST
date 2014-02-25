#include "BuiltinType/Init.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/List.h"
#include "BuiltinType/Bool.h"
#include "BuiltinType/Null.h"

namespace BuiltinType {
    void InitState() {
        Integer::InitState();
        Double::InitState();
        String::InitState();
        List::InitState();
        Bool::InitState();
        Null::InitState();
    }

    void Init(const pObject& obj) {
        obj["Integer"] = Integer::STATE;
        obj["String"] = String::STATE;
        obj["Double"] = Double::STATE;
        obj["List"] = List::STATE;
        obj["Bool"] = Bool::STATE;
        obj["true"] = Bool::TRUE;
        obj["false"] = Bool::FALSE;
        obj["null"] = Null::Obj;
        obj["Null"] = Null::STATE;
    }
}
