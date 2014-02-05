#include "BuiltinType/Integer.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/String.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"
#include <iostream>
#include <sstream>

namespace BuiltinType {
    namespace Integer {
        BaseType::ObjPtr STATE;

        BaseType::Object* Create(std::string str) {
            std::stringstream in(str);
            Inner red;
            in >> red;
            if (!in) {
                //TODO: Add an exception.
            }
            return Create(red);
        }

        BaseType::Object* Create(Inner num) {
            BaseType::Object* ret = new BaseType::PtrObject<Inner>(new Inner(num), STATE);
            return ret;
        }

        void InitState() {
            if ((BaseType::Object*)STATE)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            STATE->setAttr("__add__", new BaseType::BuiltinFunc(__add__));
            STATE->setAttr("__minus__", new BaseType::BuiltinFunc(__minus__));
            STATE->setAttr("__mul__", new BaseType::BuiltinFunc(__mul__));
            STATE->setAttr("__div__", new BaseType::BuiltinFunc(__div__));
            STATE->setAttr("__mod__", new BaseType::BuiltinFunc(__mod__));
            STATE->setAttr("__str__", new BaseType::BuiltinFunc(__str__));
        }

#define DEF_OPER(NAME, OPER) DEF_BUILTIN_FUNC(NAME) {\
    CHECK_ARG_SIZE(==2);\
    Inner& lhs = GET_PTR_ARG(0, Inner);\
    BaseType::Object* rhsI = GET_ARG(1, BaseType::Object);\
    BaseType::Object* rhsT = rhsI->getAttr("__state__");\
    if (rhsT == Integer::STATE)\
        return Create(lhs OPER ToolKit::GetInner<Inner>(rhsI));\
    else\
        return Double::Create(lhs OPER ToolKit::GetInner<Double::Inner>(rhsI));\
}
        DEF_OPER(__add__, +)
        DEF_OPER(__minus__, -)
        DEF_OPER(__mul__, *)
        DEF_OPER(__div__, /)

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

