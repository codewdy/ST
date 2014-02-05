#include "BuiltinType/String.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/Bool.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"

namespace BuiltinType {
    namespace String {
        BaseType::ObjPtr STATE;

        BaseType::Object* Create(Inner num) {
            BaseType::Object* ret = new BaseType::PtrObject<Inner>(new Inner(num), STATE);
            std::cout << num << std::endl;
            return ret;
        }

        void InitState() {
            if ((BaseType::Object*)STATE)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            STATE->setAttr("__add__", new BaseType::BuiltinFunc(__add__));
            STATE->setAttr("__mul__", new BaseType::BuiltinFunc(__mul__));
            STATE->setAttr("__str__", new BaseType::BuiltinFunc(__str__));
            STATE->setAttr("__equal__", new BaseType::BuiltinFunc(__equal__));
            STATE->setAttr("__less_than__", new BaseType::BuiltinFunc(__less_than__));
        }

        DEF_BUILTIN_FUNC(__add__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            Inner& rhs = ToolKit::GetInner<Inner>(CALC(args[1], __str__));
            return Create(lhs + rhs);
        }

#define DEF_COMP_OPER(NAME, OPER) DEF_BUILTIN_FUNC(NAME) {\
            CHECK_ARG_SIZE(==2);\
            Inner& lhs = GET_PTR_ARG(0, Inner);\
            Inner& rhs = ToolKit::GetInner<Inner>(CALC(args[1], __str__));\
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
            return Create(ret);
        }

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            return GET_ARG(0, BaseType::PtrObject<Inner>);
        }
    }
}

