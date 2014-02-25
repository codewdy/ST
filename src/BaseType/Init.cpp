#include "BaseType/Init.h"
#include "BaseType/Object.h"
#include "BaseType/State.h"
#include "BaseType/Func.h"
#include "BaseType/SimpleFunc.h"
#include "BaseType/BuiltinFunc.h"
#include "BaseType/ObjectFunc.h"
#include "BaseType/PtrObject.h"
#include "BaseType/Namespace.h"
#include "BaseType/Import.h"
#include "ToolKit.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Bool.h"
#include "BaseType/Excpt.h"
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
    pObject Excpt::AttrNotFound;
    pObject Excpt::ArgCountError;
    pObject Excpt::STCDecodeError;
    pObject Excpt::STCRuntimeStackError;
    pObject Excpt::ConvertError;
    pObject Excpt::IndexError;
    pObject FuncImport;

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
        Object::STATE["__str__"] = ST_FUNC_ARG(==1, {
            std::ostringstream ret;
            ret << "[Object at " << args[0].GetPtr() << "]";
            return ret.str();
        });
        Object::STATE["__equal__"] = ST_FUNC_ARG(==2, {
            return args[0].ref_equal(args[1]);
        });
        Object::STATE["__not_equal__"] = ST_FUNC_ARG(==2, {
            return !(args[0] == args[1]);
        });
        Object::STATE["__greater_than__"] = ST_FUNC_ARG(==2, {
            return args[1] < args[0];
        });
        Object::STATE["__not_less__"] = ST_FUNC_ARG(==2, {
            return !(args[0] < args[1]);
        });
        Object::STATE["__not_greater__"] = ST_FUNC_ARG(==2, {
            return !(args[1] < args[0]);
        });
        Excpt::AttrNotFound = new State;
        Excpt::AttrNotFound["__str__"] = ST_FUNC_ARG(==1, {
                return args[0]["obj"]["__str__"]() + args[0]["attr"];
        });
#define ST_DEF_EXCPT(CLASS)\
        Excpt::CLASS = new State;\
        Excpt::CLASS["__str__"] = ST_FUNC_ARG(==1, {\
            return #CLASS;\
        });
        ST_DEF_EXCPT(ArgCountError)
        ST_DEF_EXCPT(STCDecodeError)
        ST_DEF_EXCPT(STCRuntimeStackError)
        ST_DEF_EXCPT(ConvertError)
        ST_DEF_EXCPT(IndexError)
        FuncImport = Import;
    }

    void Init(const pObject& ret) {
        ret["Object"] = Object::STATE;
        ret["Func"] = Func::STATE;
        ret["SimpleFunc"] = SimpleFunc::STATE;
        ret["ObjectFunc"] = ObjectFunc::STATE;
        ret["BuiltinFunc"] = BuiltinFunc::STATE;
        ret["Namespace"] = Namespace::STATE;
        ret["ObjectNamespace"] = ObjectNamespace::STATE;
        ret["AttrNotFound"] = Excpt::AttrNotFound;
        ret["ArgCountError"] = Excpt::ArgCountError;
        ret["STCDecodeError"] = Excpt::STCDecodeError;
        ret["STCRuntimeError"] = Excpt::STCRuntimeStackError;
        ret["ConvertError"] = Excpt::ConvertError;
        ret["IndexError"] = Excpt::IndexError;
        ret["import"] = FuncImport;
    }
}

