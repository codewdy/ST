#include "BuiltinType/String.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/Bool.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"

namespace BuiltinType {
    namespace String {
        pObject STATE;

        pObject Create(const Inner& num) {
            std::cout << num << std::endl;
            return ToolKit::CreateObj(STATE, num);
        }

        pObject Create(Inner&& num) {
            std::cout << num << std::endl;
            return ToolKit::CreateObj(STATE, std::move(num));
        }

        void InitState() {
            if (STATE.ref_not_equal(nullptr))
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            SET_FUNC(STATE, __add__);
            SET_FUNC(STATE, __mul__);
            SET_FUNC(STATE, __str__);
            SET_FUNC(STATE, __equal__);
            SET_FUNC(STATE, __less_than__);
        }

        DEF_BUILTIN_FUNC(__add__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            Inner& rhs = args[1]["__str__"].To<Inner>();
            return Create(lhs + rhs);
        }

#define DEF_COMP_OPER(NAME, OPER) DEF_BUILTIN_FUNC(NAME) {\
            CHECK_ARG_SIZE(==2);\
            Inner& lhs = GET_PTR_ARG(0, Inner);\
            Inner& rhs = args[1]["__str__"]().To<Inner>();\
            return Bool::Create(lhs OPER rhs);\
        }
        DEF_COMP_OPER(__equal__, ==)
        DEF_COMP_OPER(__less_than__, <)

        DEF_BUILTIN_FUNC(__mul__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            int rhs = GET_PTR_ARG(1, Integer::Inner);
            Inner ret;
            for (int i = 0; i < rhs; i++)
                ret += lhs;
            return Create(std::move(ret));
        }

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            return args[0];
        }
    }
}

