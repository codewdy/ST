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
        void RunASTC();
        void HandleException();
    public:
        void PushObject(BaseType::Object* obj);
        BaseType::ObjPtr PopObject();
        BaseType::ObjPtr& TopObject();
        void PushContext(const Context& obj);
        void PopContext();
        Context& TopContext();
        void Run();
        void Call(int num);
    };
}
#endif
