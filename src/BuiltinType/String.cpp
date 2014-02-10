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

            STATE["__add__"] = BUILTIN_FUNC_LAMBDA_ARG(==2, {
                Inner& lhs = GET_PTR_ARG(0, Inner);
                Inner& rhs = args[1]["__str__"]().To<Inner>();
                return lhs + rhs;
            });

            STATE["__mul__"] = BUILTIN_FUNC_LAMBDA_ARG(==2, {
                Inner& lhs = GET_PTR_ARG(0, Inner);
                int rhs = GET_PTR_ARG(1, Integer::Inner);
                Inner ret;
                for (int i = 0; i < rhs; i++)
                    ret += lhs;
                return std::move(ret);
            });

            STATE["__str__"] = BUILTIN_FUNC_LAMBDA_ARG(==1, {
                return args[0];
            });

#define DEF_OPER(OPER) BUILTIN_FUNC_LAMBDA_ARG(==2, {\
                Inner& lhs = GET_PTR_ARG(0, Inner);\
                Inner& rhs = args[1]["__str__"]().To<Inner>();\
                return lhs OPER rhs;\
            })
            STATE["__equal__"] = DEF_OPER(==);
            STATE["__less_than__"] = DEF_OPER(<);
        }
    }
}

