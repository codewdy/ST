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
    ObjPtr Object::STATE;
    ObjPtr State::STATE;
    ObjPtr Func::STATE;
    ObjPtr SimpleFunc::STATE;
    ObjPtr ObjectFunc::STATE;
    ObjPtr BuiltinFunc::STATE;
    ObjPtr Namespace::STATE;
    ObjPtr ObjectNamespace::STATE;
    ObjPtr PtrObjectSTATE;

    DEF_BUILTIN_FUNC(obj_str) {
        CHECK_ARG_SIZE(==1);
        std::ostringstream ret;
        ret << "[Object at "<< args[0] << "]";
        return BuiltinType::String::Create(ret.str());
    }

    DEF_BUILTIN_FUNC(obj_eq) {
        CHECK_ARG_SIZE(==2);
        return BuiltinType::Bool::Create(args[0] == args[1]);
    }

    DEF_BUILTIN_FUNC(obj_ne) {
        CHECK_ARG_SIZE(==2);
        Object* eq = CALC(args[0], __equal__, args[1]);
        return CALC(eq, __not__);
    }

    DEF_BUILTIN_FUNC(obj_gt) {
        CHECK_ARG_SIZE(==2);
        return CALC(args[1], __less_than__, args[0]);
    }

    DEF_BUILTIN_FUNC(obj_nl) {
        CHECK_ARG_SIZE(==2);
        Object* eq = CALC(args[0], __less_than__, args[1]);
        return CALC(eq, __not__);
    }

    DEF_BUILTIN_FUNC(obj_ng) {
        CHECK_ARG_SIZE(==2);
        Object* eq = CALC(args[0], __greater_than__, args[1]);
        return CALC(eq, __not__);
    }

    void InitState() {
        Object::STATE = new State(0);
        Func::STATE = new State();
        State::STATE = new State(Func::STATE);
        Object::STATE->setAttr("__state__", State::STATE);
        Func::STATE->setAttr("__state__", State::STATE);
        State::STATE->setAttr("__state__", State::STATE);
        SimpleFunc::STATE = new State(Func::STATE);
        ObjectFunc::STATE = new State(Func::STATE);
        BuiltinFunc::STATE = new State(Func::STATE);
        PtrObjectSTATE = new State();
        Namespace::STATE = new State();
        ObjectNamespace::STATE = new State(Namespace::STATE);
        Object::STATE->setAttr("__str__", new BuiltinFunc(obj_str));
        Object::STATE->setAttr("__equal__", new BuiltinFunc(obj_eq));
        Object::STATE->setAttr("__not_equal__", new BuiltinFunc(obj_ne));
        Object::STATE->setAttr("__greater_than__", new BuiltinFunc(obj_gt));
        Object::STATE->setAttr("__not_less__", new BuiltinFunc(obj_nl));
        Object::STATE->setAttr("__not_greater__", new BuiltinFunc(obj_ng));
    }

    void Init(Object* ret) {
        ret->setAttr("Object", Object::STATE);
        ret->setAttr("State", State::STATE);
        ret->setAttr("Func", Func::STATE);
        ret->setAttr("SimpleFunc", SimpleFunc::STATE);
        ret->setAttr("ObjectFunc", ObjectFunc::STATE);
        ret->setAttr("BuiltinFunc", BuiltinFunc::STATE);
        ret->setAttr("Namespace", Namespace::STATE);
        ret->setAttr("ObjectNamespace", ObjectNamespace::STATE);
    }
}

