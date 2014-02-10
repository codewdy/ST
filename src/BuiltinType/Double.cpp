#include "BuiltinType/Double.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Bool.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"
#include <iostream>
#include <sstream>

namespace BuiltinType {
    namespace Double {
        pObject STATE;

        pObject Create(const std::string& str) {
            std::stringstream in(str);
            Inner red;
            in >> red;
            if (!in) {
                //TODO: Add an exception.
            }
            return Create(red);
        }

        pObject Create(Inner num) {
            return ToolKit::CreateObj(STATE, num);
        }

        void InitState() {
            if (STATE.ref_not_equal(nullptr))
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
#define DEF_OPER(OPER) BUILTIN_FUNC_LAMBDA_ARG(==2, {\
                Inner& lhs = GET_PTR_ARG(0, Inner);\
                pObject rhsT = GET_ARG_STATE(1);\
                if (rhsT.ref_equal(Double::STATE))\
                    return lhs OPER GET_PTR_ARG(1, Inner);\
                else\
                    return lhs OPER GET_PTR_ARG(1, Integer::Inner);\
            })
            STATE["__add__"] = DEF_OPER(+);
            STATE["__minus__"] = DEF_OPER(-);
            STATE["__mul__"] = DEF_OPER(*);
            STATE["__div__"] = DEF_OPER(/);
            STATE["__equal__"] = DEF_OPER(==);
            STATE["__less_than__"] = DEF_OPER(<);
            STATE["__str__"] = BUILTIN_FUNC_LAMBDA_ARG(==1, {
                std::ostringstream ret;
                ret << GET_PTR_ARG(0, Inner);
                return ret.str();
            });
        }
    }
}

