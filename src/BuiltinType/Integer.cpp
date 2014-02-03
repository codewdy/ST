#include "BuiltinType/Integer.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"

namespace BuiltinType {
    namespace Integer {
        BaseType::ObjPtr STATE;

        BaseType::Object* Create(std::string str) {
            std::stringstream in(str);
            int red;
            in >> red;
            if (!in) {
                //TODO: Add an exception.
            }
            return Create(red);
        }

        BaseType::Object* Create(int num) {
            BaseType::Object* ret = new BaseType::PtrObject<IntegerInner>(new int(num), STATE);
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
        }

#define DEF_OPER(NAME, OPER) DEF_BUILTIN_FUNC(NAME) {\
    CHECK_ARG_SIZE(==2)\
    int lhs = *GET_ARG(0, BaseType::PtrObject<IntegerInner>)->ptr;\
    int rhs = *GET_ARG(1, BaseType::PtrObject<IntegerInner>)->ptr;\
    std::cout << lhs << #NAME << rhs << std::endl;\
    return Create(lhs OPER rhs);\
}

        DEF_OPER(__add__, +)
        DEF_OPER(__minus__, -)
        DEF_OPER(__mul__, *)
        DEF_OPER(__div__, /)
        DEF_OPER(__mod__, %)
    }
}

