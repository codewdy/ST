#ifndef ST_7823912731_BASETYPE_BUILTINFUNC
#define ST_7823912731_BASETYPE_BUILTINFUNC

#include "Func.h"

namespace BaseType {
    class BuiltinFunc : public Func {
    public:
        static ObjPtr STATE;
        typedef Object* (*pFunc)(const std::vector<Object*>& args);
        pFunc func;
        virtual void run(Runtime::VM& vm, int num);
        BuiltinFunc(pFunc _func) : Func(STATE), func(_func) {}
    };
#define DEF_BUILTIN_FUNC(FUNC_NAME) BaseType::Object* FUNC_NAME(const std::vector<BaseType::Object*>& args)
#define CHECK_ARG_SIZE(CONDITION) if (!(args.size() CONDITION)) {/*TODO:Add Exception.*/}
    template <class T>
    inline T* GetArgInner(Object* t) {
        T* ret = dynamic_cast<T*>(t);
        if (!ret) {
            /*TODO:Add Exception.*/
        }
        return ret;
    }
#define GET_ARG(num, type) BaseType::GetArgInner<type>(args[num])
}

#endif
