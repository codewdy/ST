#include "BuiltinType/List.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/Bool.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"

namespace BuiltinType {
    namespace List {
        BaseType::ObjPtr STATE, IterSTATE;

        BaseType::Object* Create(Inner& vars) {
            return ToolKit::CreateObj(STATE, vars);
        }

        void InitState() {
            if ((BaseType::Object*)STATE)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            STATE->setAttr("__add__", new BaseType::BuiltinFunc(__add__));
            STATE->setAttr("__mul__", new BaseType::BuiltinFunc(__mul__));
            STATE->setAttr("__str__", new BaseType::BuiltinFunc(__str__));
            STATE->setAttr("__get_element__", new BaseType::BuiltinFunc(__get_element__));
            STATE->setAttr("__iter__", new BaseType::BuiltinFunc(__iter__));
            IterSTATE = new BaseType::State;
            IterSTATE->setAttr("__next__", new BaseType::BuiltinFunc(Iter__next__));
            IterSTATE->setAttr("__is_end__", new BaseType::BuiltinFunc(Iter__is_end__));
            IterSTATE->setAttr("__get__", new BaseType::BuiltinFunc(Iter__get__));
        }

        DEF_BUILTIN_FUNC(__add__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            Inner& rhs = GET_PTR_ARG(1, Inner);
            Inner ret(lhs);
            ret.insert(ret.end(), rhs.begin(), rhs.end());
            return Create(ret);
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

        DEF_BUILTIN_FUNC(__get_element__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            int rhs = GET_PTR_ARG(1, Integer::Inner);
            if (lhs.size() >= rhs) {
                //TODO:Add an exception.
            }
            return lhs[rhs];
        }

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            Inner arg = GET_PTR_ARG(0, Inner);
            String::Inner ret = "[";
            for (int i = 0; i < arg.size(); i++){
                BaseType::Object* str = CALC(arg[i], __str__);
                ret += ToolKit::GetInner<String::Inner>(str);
                if (i != arg.size() - 1)
                    ret += ", ";
            }
            ret += "]";
            return String::Create(ret);
        }

        DEF_BUILTIN_FUNC(__iter__) {
            CHECK_ARG_SIZE(==1);
            BaseType::Object* ret = new BaseType::Object(IterSTATE);
            ret->setAttr("__array__", args[0]);
            ret->setAttr("__index__", Integer::Create(0));
            return ret;
        }

        DEF_BUILTIN_FUNC(Iter__next__) {
            CHECK_ARG_SIZE(==1);
            BaseType::Object* ret = new BaseType::Object(IterSTATE);
            ret->setAttr("__array__", args[0]->getAttr("__array__"));
            Integer::Inner& idx = ToolKit::GetInner<Integer::Inner>(args[0]->getAttr("__index__"));
            ret->setAttr("__index__", Integer::Create(idx + 1));
            return ret;
        }

        DEF_BUILTIN_FUNC(Iter__is_end__) {
            CHECK_ARG_SIZE(==1);
            Inner arr = ToolKit::GetInner<Inner>(args[0]->getAttr("__array__"));
            Integer::Inner& idx = ToolKit::GetInner<Integer::Inner>(args[0]->getAttr("__index__"));
            return Bool::Create(arr.size() <= idx);
        }

        DEF_BUILTIN_FUNC(Iter__get__) {
            CHECK_ARG_SIZE(==1);
            Inner arr = ToolKit::GetInner<Inner>(args[0]->getAttr("__array__"));
            Integer::Inner& idx = ToolKit::GetInner<Integer::Inner>(args[0]->getAttr("__index__"));
            if (arr.size() >= idx) {
                //TODO: Add an exception.
            }
            return arr[idx];
        }
    }
}

