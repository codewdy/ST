#ifndef ST_87612389123_RUNTIME_VM
#define ST_87612389123_RUNTIME_VM

#include <stack>
#include "Context.h"

namespace Runtime {
    class VM {
        typedef std::stack<Context> ContextStack;
        typedef std::stack<BaseType::ObjPtr> ObjectStack;
        ContextStack Contexts;
        ObjectStack Objects;
        std::vector<std::string> FuncArgs;
        void RunASTC();
        void HandleException();
        VM(){}
    public:
        VM(STC::STC* stc);
        void PushObject(BaseType::Object* obj);
        BaseType::ObjPtr PopObject();
        BaseType::ObjPtr& TopObject();
        void PushContext(const Context& ctx);
        void PopContext();
        Context& TopContext();
        void Run();
        void Call(int num);
        static BaseType::Object* CreateGlobal();
        static BaseType::Object* Calc(BaseType::Object* func, std::vector<BaseType::Object*> args);
    };
}
#endif
