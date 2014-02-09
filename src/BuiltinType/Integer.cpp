#include "BuiltinType/Integer.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Bool.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"
#include <iostream>
#include <sstream>

namespace BuiltinType {
    namespace Integer {
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
            SET_FUNC(STATE, __add__);
            SET_FUNC(STATE, __minus__);
            SET_FUNC(STATE, __mul__);
            SET_FUNC(STATE, __div__);
            SET_FUNC(STATE, __mod__);
            SET_FUNC(STATE, __str__);
            SET_FUNC(STATE, __equal__);
            SET_FUNC(STATE, __less_than__);
        }

#define DEF_OPER(NAME, OPER) DEF_BUILTIN_FUNC(NAME) {\
            CHECK_ARG_SIZE(==2);\
            Inner& lhs = GET_PTR_ARG(0, Inner);\
            pObject rhsT = GET_ARG_STATE(1);\
            if (rhsT.ref_equal(Integer::STATE))\
                return Create(lhs OPER GET_PTR_ARG(1, Inner));\
            else\
                return Double::Create(lhs OPER GET_PTR_ARG(1, Double::Inner));\
        }
        DEF_OPER(__add__, +)
        DEF_OPER(__minus__, -)
        DEF_OPER(__mul__, *)
        DEF_OPER(__div__, /)

#define DEF_COMP_OPER(NAME, OPER) DEF_BUILTIN_FUNC(NAME) {\
            CHECK_ARG_SIZE(==2);\
            Inner& lhs = GET_PTR_ARG(0, Inner);\
            pObject rhsT = GET_ARG_STATE(1);\
            if (rhsT.ref_equal(Integer::STATE))\
                return Bool::Create(lhs OPER GET_PTR_ARG(1, Inner));\
            else\
                return Bool::Create(lhs OPER GET_PTR_ARG(1, Double::Inner));\
        }
        DEF_COMP_OPER(__equal__, ==)
        DEF_COMP_OPER(__less_than__, <)

        DEF_BUILTIN_FUNC(__mod__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            Inner& rhs = GET_PTR_ARG(1, Inner);
            return Create(lhs % rhs);
        }

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            std::ostringstream ret;
            ret << GET_PTR_ARG(0, Inner);
            return String::Create(ret.str());
        }
    }
}

