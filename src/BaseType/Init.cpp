#include "BaseType/Init.h"
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/Func.h"
#include "BaseType/SimpleFunc.h"
#include "BaseType/BuiltinFunc.h"
#include "BaseType/ObjectFunc.h"
#include "BaseType/PtrObject.h"
#include "BaseType/Namespace.h"
#include "ToolKit.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Bool.h"
#include <iostream>
#include <sstream>
#include <string>

namespace BaseType {
    pObject Object::STATE;
    pObject State::STATE;
    pObject Func::STATE;
    pObject SimpleFunc::STATE;
    pObject ObjectFunc::STATE;
    pObject BuiltinFunc::STATE;
    pObject Namespace::STATE;
    pObject ObjectNamespace::STATE;
    pObject PtrObjectSTATE;

    DEF_BUILTIN_FUNC(obj_str) {
        CHECK_ARG_SIZE(==1);
        std::ostringstream ret;
        ret << "[Object at " << args[0].GetPtr() << "]";
        return BuiltinType::String::Create(ret.str());
    }

    DEF_BUILTIN_FUNC(obj_eq) {
        CHECK_ARG_SIZE(==2);
        return BuiltinType::Bool::Create(args[0].ref_equal(args[1]));
    }

    DEF_BUILTIN_FUNC(obj_ne) {
        CHECK_ARG_SIZE(==2);
        return !(args[0] == args[1]);
    }

    DEF_BUILTIN_FUNC(obj_gt) {
        CHECK_ARG_SIZE(==2);
        return (args[1] < args[0]);
    }

    DEF_BUILTIN_FUNC(obj_nl) {
        CHECK_ARG_SIZE(==2);
        return !(args[0] < args[1]);
    }

    DEF_BUILTIN_FUNC(obj_ng) {
        CHECK_ARG_SIZE(==2);
        return !(args[1] < args[0]);
    }

    void InitState() {
        Object::STATE = new State(0);
        Func::STATE = new State();
        State::STATE = new State(Func::STATE);
        Object::STATE["__state__"] = State::STATE;
        Func::STATE["__state__"] = State::STATE;
        State::STATE["__state__"] = State::STATE;
        SimpleFunc::STATE = new State(Func::STATE);
        ObjectFunc::STATE = new State(Func::STATE);
        BuiltinFunc::STATE = new State(Func::STATE);
        PtrObjectSTATE = new State();
        Namespace::STATE = new State();
        ObjectNamespace::STATE = new State(Namespace::STATE);
        ToolKit::SetFunc(Object::STATE, "__str__", obj_str);
        ToolKit::SetFunc(Object::STATE, "__equal__", obj_eq);
        ToolKit::SetFunc(Object::STATE, "__not_equal__", obj_ne);
        ToolKit::SetFunc(Object::STATE, "__greater_than__", obj_gt);
        ToolKit::SetFunc(Object::STATE, "__not_less__", obj_nl);
        ToolKit::SetFunc(Object::STATE, "__not_greater__", obj_ng);
    }

    void Init(const pObject& ret) {
        ret["Object"] = Object::STATE;
        ret["Func"] = Func::STATE;
        ret["SimpleFunc"] = SimpleFunc::STATE;
        ret["ObjectFunc"] = ObjectFunc::STATE;
        ret["BuiltinFunc"] = BuiltinFunc::STATE;
        ret["Namespace"] = Namespace::STATE;
        ret["ObjectNamespace"] = ObjectNamespace::STATE;
    }
}

