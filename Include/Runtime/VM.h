#ifndef ST_87612389123_RUNTIME_VM
#define ST_87612389123_RUNTIME_VM

#include <stack>
#include "Context.h"

namespace Runtime {
    class VM {
        typedef std::stack<Context> ContextStack;
        typedef std::stack<pObject> ObjectStack;
        struct TryElement {
            std::size_t CtxSize, ObjSize;
            STC::STC* CATCH;
        };
        typedef std::stack<TryElement> TryStack;
        ContextStack Contexts;
        ObjectStack Objects;
        TryStack Trys;
        std::vector<std::string> FuncArgs;
        void RunASTC();
        void HandleException();
        VM(){}
    public:
        VM(STC::STC* stc);
        void PushObject(const pObject& obj);
        void PushObject(pObject&& obj);
        pObject PopObject();
        pObject& TopObject();
        void PushContext(Context&& ctx);
        void PopContext();
        Context& TopContext();
        void Run();
        void Call(int num);
        static pObject CreateGlobal();
        static pObject Calc(const pObject& func, const std::vector<pObject>& args);
        static pObject Calc(const pObject& func, std::vector<pObject>&& args);
    };
}
#endif
