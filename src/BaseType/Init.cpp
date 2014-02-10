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
    pObject Object::ExcptAttrNotFound;

    void InitState() {
        Object::STATE = new State(nullptr);
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
        Object::STATE["__str__"] = BUILTIN_FUNC_LAMBDA_ARG(==1, {
            std::ostringstream ret;
            ret << "[Object at " << args[0].GetPtr() << "]";
            return BuiltinType::String::Create(ret.str());
        });
        Object::STATE["__equal__"] = BUILTIN_FUNC_LAMBDA_ARG(==2, {
            return BuiltinType::Bool::Create(args[0].ref_equal(args[1]));
        });
        Object::STATE["__not_equal__"] = BUILTIN_FUNC_LAMBDA_ARG(==2, {
            return !(args[0] == args[1]);
        });
        Object::STATE["__greater_than__"] = BUILTIN_FUNC_LAMBDA_ARG(==2, {
            return args[1] < args[0];
        });
        Object::STATE["__not_less__"] = BUILTIN_FUNC_LAMBDA_ARG(==2, {
            return !(args[0] < args[1]);
        });
        Object::STATE["__not_greater__"] = BUILTIN_FUNC_LAMBDA_ARG(==2, {
            return !(args[1] < args[0]);
        });
        Object::ExcptAttrNotFound = new State;
        Object::ExcptAttrNotFound["__str__"] = BUILTIN_FUNC_LAMBDA_ARG(==1, {
                return args[0]["obj"]["__str__"]() + args[0]["attr"];
        });
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

