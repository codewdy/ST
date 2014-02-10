#include "BuiltinType/Integer.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Bool.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "BaseType/Excpt.h"
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
                ST_RAISE(VM, {{"__state__", BaseType::Excpt::ConvertError}});
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
#define ST_DEF_OPER(OPER) ST_FUNC_ARG(==2, {\
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);\
                pObject rhsT = ST_GET_ARG_STATE(1);\
                if (rhsT.ref_equal(Integer::STATE))\
                    return lhs OPER ST_GET_PTR_ARG(1, Inner);\
                else\
                    return lhs OPER ST_GET_PTR_ARG(1, Double::Inner);\
            })
            STATE["__add__"] = ST_DEF_OPER(+);
            STATE["__minus__"] = ST_DEF_OPER(-);
            STATE["__mul__"] = ST_DEF_OPER(*);
            STATE["__div__"] = ST_DEF_OPER(/);
            STATE["__mod__"] = ST_FUNC_ARG(==2, {
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);
                Inner& rhs = ST_GET_PTR_ARG(1, Inner);
                return lhs % rhs;
            });
            STATE["__equal__"] = ST_DEF_OPER(==);
            STATE["__less_than__"] = ST_DEF_OPER(<);
            STATE["__str__"] = ST_FUNC_ARG(==1, {
                std::ostringstream ret;
                ret << ST_GET_PTR_ARG(0, Inner);
                return ret.str();
            });
        }
    }
}

