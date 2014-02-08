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
            if (STATE != nullptr)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            SET_FUNC(STATE, __and__);
            SET_FUNC(STATE, __or__);
            SET_FUNC(STATE, __not__);
            SET_FUNC(STATE, __str__);
            TRUE = ToolKit::CreateObj(STATE, true);
            FALSE = ToolKit::CreateObj(STATE, false);
        }

#define DEF_OPER(NAME, OPER) DEF_BUILTIN_FUNC(NAME) {\
    CHECK_ARG_SIZE(==2);\
    Inner& lhs = GET_PTR_ARG(0, Inner);\
    Inner& rhs = GET_PTR_ARG(1, Inner);\
    return Create(lhs OPER rhs);\
}

        DEF_OPER(__and__, &&)
        DEF_OPER(__or__, ||)

        DEF_BUILTIN_FUNC(__not__) {
            CHECK_ARG_SIZE(==1);
            return Create(!GET_PTR_ARG(0, Inner));
        }

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            return String::Create(GET_PTR_ARG(0, Inner) ? "true" : "false");
        }
    }
}

