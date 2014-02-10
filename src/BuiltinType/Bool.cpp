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
    namespace Bool {
        pObject STATE, TRUE, FALSE;

        pObject Create(Inner num) {
            return num ? TRUE : FALSE;
        }

        void InitState() {
            if (STATE.ref_not_equal(nullptr))
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
#define ST_DEF_OPER(OPER) ST_FUNC_ARG(==2, {\
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);\
                Inner& rhs = ST_GET_PTR_ARG(1, Inner);\
                return lhs OPER rhs;\
            })
            STATE["__and__"] = ST_DEF_OPER(&&);
            STATE["__or__"] = ST_DEF_OPER(||);
            STATE["__not__"] = ST_FUNC_ARG(==1, {
                return !ST_GET_PTR_ARG(0, Inner);
            });
            STATE["__str__"] = ST_FUNC_ARG(==1, {
                return ST_GET_PTR_ARG(0, Inner) ? "true" : "false";
            });
            TRUE = ToolKit::CreateObj(STATE, true);
            FALSE = ToolKit::CreateObj(STATE, false);
        }
    }
}

