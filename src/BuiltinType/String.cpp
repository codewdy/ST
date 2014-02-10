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

            STATE["__add__"] = ST_FUNC_ARG(==2, {
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);
                Inner& rhs = args[1]["__str__"]().To<Inner>();
                return lhs + rhs;
            });

            STATE["__mul__"] = ST_FUNC_ARG(==2, {
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);
                int rhs = ST_GET_PTR_ARG(1, Integer::Inner);
                Inner ret;
                for (int i = 0; i < rhs; i++)
                    ret += lhs;
                return std::move(ret);
            });

            STATE["__str__"] = ST_FUNC_ARG(==1, {
                return args[0];
            });

#define ST_DEF_OPER(OPER) ST_FUNC_ARG(==2, {\
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);\
                Inner& rhs = args[1]["__str__"]().To<Inner>();\
                return lhs OPER rhs;\
            })
            STATE["__equal__"] = ST_DEF_OPER(==);
            STATE["__less_than__"] = ST_DEF_OPER(<);
        }
    }
}

