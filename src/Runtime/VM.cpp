#include "Runtime/VM.h"
#include "BaseType/Object.h"
#include "BaseType/Func.h"
#include "BaseType/SimpleFunc.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/List.h"
#include "BuiltinType/Bool.h"
#include "BaseType/Namespace.h"
#include "BaseType/Init.h"
#include "BuiltinType/Init.h"
#include "ToolKit.h"
#include <iostream>

namespace Runtime {
    VM::VM(STC::STC* stc) {
        pObject glb = CreateGlobal();
        PushContext(Context(glb, glb, stc));
    }

    void VM::PushObject(const pObject& obj) {
        Objects.push(obj);
    }

    void VM::PushObject(pObject&& obj) {
        Objects.push(std::move(obj));
    }

    pObject VM::PopObject() {
        if (Objects.empty()) {
            //TODO: Add an exception.
        }
        pObject ret = Objects.top();
        Objects.pop();
        return std::move(ret);
    }

    pObject& VM::TopObject() {
        if (Objects.empty()) {
            //TODO: Add an exception,
        }
        return Objects.top();
    }

    void VM::PushContext(const Context& ctx) {
        Contexts.push(ctx);
    }

    void VM::PushContext(Context&& ctx) {
        Contexts.push(std::move(ctx));
    }

    void VM::PopContext() {
        if (Contexts.empty()) {
            //TODO: Add an excetion.
        }
        Contexts.pop();
    }

    Context& VM::TopContext() {
        if (Contexts.empty()) {
            //TODO: Add an excetion.
        }
        return Contexts.top();
    }

    void VM::Run() {
        while (!Contexts.empty()) {
            RunASTC();
        }
    }

    void VM::Call(int num) {
        BaseType::Object *func = PopObject(), *tmp;
        while ((tmp = func->getAttr("__exec__")) != func)
            func = tmp;
        ((BaseType::Func*)func)->run(*this, num);
    }

    void VM::RunASTC() {
        try {
            STC::STC* stc = TopContext().code;
            if (!stc) {
                PopContext();
                return;
            }
            TopContext().code = stc->next;
            switch (stc->type) {
            case STC::STC::Nop:
                break;
            case STC::STC::Pop:
                PopObject();
                break;
            case STC::STC::PushInteger:
                PushObject(BuiltinType::Integer::Create(stc->str));
                break;
            case STC::STC::PushDouble:
                PushObject(BuiltinType::Double::Create(stc->str));
                break;
            case STC::STC::PushString:
                PushObject(BuiltinType::String::Create(stc->str));
                break;
            case STC::STC::MakeList:
                {
                    BuiltinType::List::InitInner ret;
                    for (int i = 0; i < stc->num; i++)
                        ret.push_back(PopObject());
                    PushObject(BuiltinType::List::Create(ret));
                }
                break;
            case STC::STC::Call:
                Call(stc->num);
                break;
            case STC::STC::PushLocale:
                PushObject(TopContext().Locale);
                break;
            case STC::STC::PushGlobal:
                PushObject(TopContext().Global);
                break;
            case STC::STC::PushNull:
                PushObject(0);
                //TODO:Add an Null.
                break;
            case STC::STC::CopyTop:
                PushObject(TopObject());
                break;
            case STC::STC::GetAttr:
                PushObject(PopObject()->getAttr(stc->str));
                break;
            case STC::STC::SetAttr:
                {
                    pObject obj1 = PopObject();
                    pObject obj2 = PopObject();
                    obj1->setAttr(stc->str, obj2);
                }
                break;
            case STC::STC::Goto:
                TopContext().code = stc->code;
                break;
            case STC::STC::TrueGoto:
                if (ToolKit::GetInner<BuiltinType::Bool::Inner>(PopObject()))
                    TopContext().code = stc->code;
                break;
            case STC::STC::FalseGoto:
                if (!ToolKit::GetInner<BuiltinType::Bool::Inner>(PopObject()))
                    TopContext().code = stc->code;
                break;
            case STC::STC::FuncArg:
                FuncArgs.push_back(stc->str);
                break;
            case STC::STC::DefFunc:
                {
                    BaseType::SimpleFunc * ret = new BaseType::SimpleFunc(TopContext().Global, TopContext().Locale, stc->code);
                    ret->argsName.swap(FuncArgs);
                    PushObject(ret);
                }
                break;
            case STC::STC::DefState:
                {
                    pObject ret = new BaseType::State;
                    PushContext(Context(TopContext().Global, new BaseType::ObjectNamespace(TopContext().Locale, ret), stc->code));
                    PushObject(ret);
                }
                break;
            case STC::STC::Return:
                PopContext();
                break;
            }
        } catch(int) {
            //TODO: Add handle Exception.
        }
    }

    pObject VM::CreateGlobal() {
        pObject ret = new BaseType::Namespace();
        BaseType::Init(ret);
        BuiltinType::Init(ret);
        return ret;
    }

    pObject VM::Calc(const pObject& func, const std::vector<pObject>& args) {
        VM vm;
        for (int i = args.size() - 1; i >= 0; i--)
            vm.PushObject(args[i]);
        vm.PushObject(func);
        vm.Call(args.size());
        vm.Run();
        return vm.PopObject();
    }

    pObject VM::Calc(const pObject& func, std::vector<pObject>&& args) {
        VM vm;
        for (int i = args.size() - 1; i >= 0; i--)
            vm.PushObject(std::move(args[i]));
        vm.PushObject(func);
        vm.Call(args.size());
        vm.Run();
        return vm.PopObject();
    }
}
