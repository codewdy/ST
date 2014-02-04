#include "BuiltinType/List.h"
#include "BuiltinType/Integer.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"

namespace BuiltinType {
    namespace List {
        BaseType::ObjPtr STATE;

        BaseType::Object* Create(Inner vars) {
            BaseType::Object* ret = new BaseType::PtrObject<Inner>(new Inner(vars), STATE);
            return ret;
        }

        void InitState() {
            if ((BaseType::Object*)STATE)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            STATE->setAttr("__add__", new BaseType::BuiltinFunc(__add__));
            STATE->setAttr("__mul__", new BaseType::BuiltinFunc(__mul__));
            STATE->setAttr("__str__", new BaseType::BuiltinFunc(__str__));
        }

        DEF_BUILTIN_FUNC(__mul__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            int rhs = GET_PTR_ARG(1, Integer::Inner);
            Inner ret;
            for (int i = 0; i < rhs; i++)
                ret.insert(ret.end(), lhs.begin(), lhs.end());
            return Create(ret);
        }

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            return GET_ARG(0, BaseType::PtrObject<Inner>);
        }
    }
}

