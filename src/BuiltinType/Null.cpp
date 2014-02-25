#include "BuiltinType/Bool.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/String.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"
#include <iostream>
#include <sstream>

namespace BuiltinType {
    namespace Null {
        pObject STATE, Obj;

        void InitState() {
            if (STATE.ref_not_equal(nullptr))
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            STATE["__str__"] = ST_FUNC_ARG(==1, {
                    return "null";
            });
            Obj = new BaseType::Object(STATE);
        }
    }
}

