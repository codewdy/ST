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
        pObject STATE, IterSTATE;

        pObject Create(const InitInner& vars) {
            pObject ret = ToolKit::CreateObj(STATE, Inner());
            pObject in = ret->getAttr("__inner__");
            for (pObject item : vars)
                ToolKit::GetInner<Inner>(ret).push_back(pObjectExt(item, in));
            return std::move(ret);
        }

        void InitState() {
            if (STATE != nullptr)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            SET_FUNC(STATE, __add__);
            SET_FUNC(STATE, __mul__);
            SET_FUNC(STATE, __str__);
            SET_FUNC(STATE, __get_element__);
            SET_FUNC(STATE, __iter__);
            IterSTATE = new BaseType::State;
            ToolKit::SetFunc(IterSTATE, "__next__", Iter__next__);
            ToolKit::SetFunc(IterSTATE, "__is_end__", Iter__is_end__);
            ToolKit::SetFunc(IterSTATE, "__get__", Iter__get__);
        }

        DEF_BUILTIN_FUNC(__add__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            Inner& rhs = GET_PTR_ARG(1, Inner);
            InitInner ret(lhs.begin(), lhs.end());
            ret.insert(ret.end(), rhs.begin(), rhs.end());
            return Create(ret);
        }

        DEF_BUILTIN_FUNC(__mul__) {
            CHECK_ARG_SIZE(==2);
            Inner& lhs = GET_PTR_ARG(0, Inner);
            int rhs = GET_PTR_ARG(1, Integer::Inner);
            InitInner ret;
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
            return ToolKit::GetOrigin(lhs[rhs]);
        }

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            Inner arg = GET_PTR_ARG(0, Inner);
            String::Inner ret = "[";
            for (int i = 0; i < arg.size(); i++){
                pObject str = CALC(arg[i], __str__);
                ret += ToolKit::GetInner<String::Inner>(str);
                if (i != arg.size() - 1)
                    ret += ", ";
            }
            ret += "]";
            return String::Create(std::move(ret));
        }

        DEF_BUILTIN_FUNC(__iter__) {
            CHECK_ARG_SIZE(==1);
            pObject ret = new BaseType::Object(IterSTATE);
            ret->setAttr("__array__", args[0]);
            ret->setAttr("__index__", Integer::Create(0));
            return std::move(ret);
        }

        DEF_BUILTIN_FUNC(Iter__next__) {
            CHECK_ARG_SIZE(==1);
            pObject ret = new BaseType::Object(IterSTATE);
            ret->setAttr("__array__", args[0]->getAttr("__array__"));
            Integer::Inner& idx = ToolKit::GetInner<Integer::Inner>(args[0]->getAttr("__index__"));
            ret->setAttr("__index__", Integer::Create(idx + 1));
            return std::move(ret);
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
            return ToolKit::GetOrigin(arr[idx]);
        }
    }
}

