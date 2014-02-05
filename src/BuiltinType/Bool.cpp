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
        BaseType::ObjPtr STATE, TRUE, FALSE;

        BaseType::Object* Create(Inner num) {
            return num ? TRUE : FALSE;
        }

        void InitState() {
            if ((BaseType::Object*)STATE)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            STATE->setAttr("__and__", new BaseType::BuiltinFunc(__and__));
            STATE->setAttr("__or__", new BaseType::BuiltinFunc(__or__));
            STATE->setAttr("__not__", new BaseType::BuiltinFunc(__not__));
            STATE->setAttr("__str__", new BaseType::BuiltinFunc(__str__));
            TRUE = new BaseType::PtrObject<Inner>(new bool(true), STATE);
            FALSE = new BaseType::PtrObject<Inner>(new bool(false), STATE);
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

