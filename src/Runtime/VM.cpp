#include "Runtime/VM.h"
#include "BaseType/Object.h"
#include "BaseType/Func.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Double.h"
#include "BaseType/Namespace.h"
#include "BaseType/Init.h"
#include "BuiltinType/Init.h"
#include <iostream>

namespace Runtime {
    VM::VM(STC::STC* stc) {
        BaseType::Object* glb = CreateGlobal();
        PushContext(Context(glb, glb, stc));
    }

    void VM::PushObject(BaseType::Object* obj) {
        Objects.push(obj);
    }

    BaseType::ObjPtr VM::PopObject() {
        if (Objects.empty()) {
            //TODO: Add an exception.
        }
        BaseType::ObjPtr ret = Objects.top();
        Objects.pop();
        return ret;
    }

    BaseType::ObjPtr& VM::TopObject() {
        if (Objects.empty()) {
            //TODO: Add an exception,
        }
        return Objects.top();
    }

    void VM::PushContext(const Context& ctx) {
        Contexts.push(ctx);
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
        BaseType::ObjPtr funcS = PopObject();
        BaseType::Object *func = funcS, *tmp;
        while ((tmp = func->getAttr("__exec__")) != func)
            func = tmp;
        ((BaseType::Func*)func)->run(*this, num);
    }

    void VM::RunASTC() {
        try {
            STC::STC* stc = TopContext().code;
            std::cout << stc << std::endl;
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
            case STC::STC::Call:
                Call(stc->num);
                break;
            case STC::STC::PushLocale:
                PushObject(TopContext().Locale);
                break;
            case STC::STC::PushGlobal:
                PushObject(TopContext().Global);
                break;
            case STC::STC::CopyTop:
                PushObject(TopObject());
                break;
            case STC::STC::GetAttr:
                {
                    BaseType::ObjPtr obj1 = PopObject();
                    PushObject(obj1->getAttr(stc->str));
                }
                break;
            case STC::STC::SetAttr:
                {
                    BaseType::ObjPtr obj1 = PopObject();
                    BaseType::ObjPtr obj2 = PopObject();
                    obj1->setAttr(stc->str, obj2);
                }
                break;
            default:
                std::cout << "Unhandled!" << std::endl;
            }
            BaseType::ObjPtr::GC();
        } catch(int) {
            //TODO: Add handle Exception.
        }
    }

    BaseType::Object* VM::CreateGlobal() {
        BaseType::Object* ret = new BaseType::Namespace();
        BaseType::Init(ret);
        BuiltinType::Init(ret);
        return ret;
    }
}
