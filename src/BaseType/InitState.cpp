#include "BaseType/InitState.h"
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/Func.h"
#include "BaseType/SimpleFunc.h"
#include "BaseType/BuiltinFunc.h"
#include "BaseType/ObjectFunc.h"
#include "BaseType/PtrObject.h"
#include "BaseType/Namespace.h"

namespace BaseType {
    DEF_BUILTIN_FUNC(State_exec_) {
        return new Object(args[0]);
    }

    void InitState() {
        Object::STATE = new State(0);
        State::STATE = new State();
        Object::STATE->setAttr("__state__", State::STATE);
        State::STATE->setAttr("__state__", State::STATE);
        Func::STATE = new State();
        SimpleFunc::STATE = new State(Func::STATE);
        ObjectFunc::STATE = new State(Func::STATE);
        BuiltinFunc::STATE = new State(Func::STATE);
        PtrObjectSTATE = new State();
        Namespace::STATE = new State();
        ObjectNamespace::STATE = new State();
        State::STATE->setAttr("__exec__", new BuiltinFunc(State_exec_));
    }
}

