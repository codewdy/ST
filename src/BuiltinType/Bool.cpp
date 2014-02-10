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
#define DEF_OPER(OPER) BUILTIN_FUNC_LAMBDA_ARG(==2, {\
                Inner& lhs = GET_PTR_ARG(0, Inner);\
                Inner& rhs = GET_PTR_ARG(1, Inner);\
                return lhs OPER rhs;\
            })
            STATE["__and__"] = DEF_OPER(&&);
            STATE["__or__"] = DEF_OPER(||);
            STATE["__not__"] = BUILTIN_FUNC_LAMBDA_ARG(==1, {
                return !GET_PTR_ARG(0, Inner);
            });
            STATE["__str__"] = BUILTIN_FUNC_LAMBDA_ARG(==1, {
                return GET_PTR_ARG(0, Inner) ? "true" : "false";
            });
            TRUE = ToolKit::CreateObj(STATE, true);
            FALSE = ToolKit::CreateObj(STATE, false);
        }
    }
}

