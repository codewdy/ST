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
#include "Exception.h"
#include "BaseType/Excpt.h"
#ifdef DEBUG
#include <iostream>
#endif

namespace Runtime {
    VM::VM() {
        PushContext(Context(nullptr, nullptr, nullptr));
    }

    VM::VM(STC::STC* stc) {
        PushContext(Context(nullptr, nullptr, nullptr));
        pObject glb = CreateGlobal();
        PushContext(Context(glb, glb, stc));
    }

    void VM::PushObject(const pObject& obj) {
        TopContext().objStack.push(obj);
    }

    void VM::PushObject(pObject&& obj) {
        TopContext().objStack.push(std::move(obj));
    }

    pObject VM::PopObject() {
        if (TopContext().objStack.empty()) {
            ST_RAISE(VM, {{"__state__", BaseType::Excpt::STCRuntimeStackError}});
        }
        pObject ret = TopContext().objStack.top();
        TopContext().objStack.pop();
        return std::move(ret);
    }

    pObject& VM::TopObject() {
        if (TopContext().objStack.empty()) {
            ST_RAISE(VM, {{"__state__", BaseType::Excpt::STCRuntimeStackError}});
        }
        return TopContext().objStack.top();
    }

    void VM::PushContext(Context&& ctx) {
        Contexts.push(std::move(ctx));
    }

    void VM::PopContext() {
        if (Contexts.empty()) {
            ST_RAISE(VM, {{"__state__", BaseType::Excpt::STCRuntimeStackError}});
        }
        Contexts.pop();
    }

    Context& VM::TopContext() {
        if (Contexts.empty()) {
            ST_RAISE(VM, {{"__state__", BaseType::Excpt::STCRuntimeStackError}});
        }
        return Contexts.top();
    }

    void VM::Run() {
        while (Contexts.size() > 1)
            try {
                RunASTC();
            } catch (Exception::VMException e) {
                //TODO
                /*
                std::size_t goalCtx;
                STC::STC* next = nullptr;
                if (Trys.empty())
                    goalCtx = 0;
                else {
                    TryElement t = Trys.top();
                    Trys.pop();
                    if (Contexts.size() < t.CtxSize || TopContext().objStack.size() < t.ObjSize)
                        ST_RAISE(DoubleFault);
                    while (TopContext().objStack.size() > t.ObjSize)
                        TopContext().objStack.pop();
                    next = t.CATCH;
                }
                while (Contexts.size() > goalCtx) {
                    e.trace.push_back({Contexts.top().SourceFile, Contexts.top().SourceLine});
                    Contexts.pop();
                }
                if (goalCtx)
                    TopContext().code = next;
                else
                    throw e;
                */
                throw e;
            }
    }

    void VM::Call(int num) {
        pObject func = PopObject(), tmp;
        while ((tmp = func["__exec__"]).ref_not_equal(func))
            func = tmp;
        ToolKit::SafeConvert<BaseType::Func>(func.GetPtr())->run(*this, num);
    }

    void VM::RunASTC() {
        STC::STC* stc = TopContext().code;
#ifdef DEBUG
        *(Exception::LogFile) << stc << std::endl;
        *(Exception::LogFile) << "CtxStackSize:" << Contexts.size() << std::endl;
        *(Exception::LogFile) << "StackSize:" << TopContext().objStack.size() << std::endl;
        if (TopContext().objStack.size()) {
            *(Exception::LogFile) << "Stack:" << TopObject().GetPtr() << std::endl;
        } else {
            *(Exception::LogFile) << "Stack:None" << std::endl;
        }
#endif
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
            PushObject(ToolKit::null);
            break;
        case STC::STC::PushObject:
            PushObject(BaseType::Object::STATE);
            break;
        case STC::STC::CopyTop:
            PushObject(TopObject());
            break;
        case STC::STC::GetAttr:
            PushObject(PopObject()[stc->str]);
            break;
        case STC::STC::SetAttr:
            {
                pObject obj1 = PopObject();
                pObject obj2 = PopObject();
                obj1[stc->str] = obj2;
            }
            break;
        case STC::STC::Goto:
            TopContext().code = stc->code;
            break;
        case STC::STC::TrueGoto:
            if (PopObject().To<BuiltinType::Bool::Inner>())
                TopContext().code = stc->code;
            break;
        case STC::STC::FalseGoto:
            if (!PopObject().To<BuiltinType::Bool::Inner>())
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
                pObject ret = new BaseType::State(PopObject());
                PushObject(ret);
                PushContext(Context(TopContext().Global, new BaseType::ObjectNamespace(TopContext().Locale, ret), stc->code));
            }
            break;
        case STC::STC::Return:
            {
                pObject tmp = PopObject();
                PopContext();
                PushObject(tmp);
                break;
            }
        case STC::STC::SourceFile:
            TopContext().SourceFile = stc->str;
            break;
        case STC::STC::SourceLine:
            TopContext().SourceLine = stc->num;
            break;
        case STC::STC::Try:
            //TODO
            /*
            Trys.push({Contexts.size(), TopContext().objStack.size(), stc->code});
            */
            break;
        case STC::STC::Catch:
            //TODO
            /*
            Trys.pop();
            TopContext().code = stc->code;
            */
            break;
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
