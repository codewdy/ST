#ifndef ST_9834721029_TOOLKIT
#define ST_9834721029_TOOLKIT
#include "BaseType/BuiltinFunc.h"
#include "BaseType/PtrObject.h"
#define CHECK_ARG_SIZE(CONDITION) do {if (!(args.size() CONDITION)) {/*TODO:Add Exception.*/}} while(0)
namespace ToolKit {
    template <class T>
    inline T* SafeConvert(BaseType::Object* t) {
        T* ret = dynamic_cast<T*>(t);
        if (!ret) {
            /*TODO:Add Exception.*/
        }
        return ret;
    }
    template <class T>
    inline T& GetInner(BaseType::Object* t) {
        return *SafeConvert<BaseType::PtrObject<T>>(t->getAttr("__inner__"))->ptr;
    }
    template <class T>
    inline BaseType::Object* CreateObj(BaseType::Object* state, const T& inner) {
        BaseType::Object* ret = new BaseType::Object(state);
        ret->setAttr("__inner__", new BaseType::PtrObject<T>(new T(inner)));
        return ret;
    }
}
#define GET_ARG(num, type) ToolKit::SafeConvert<type>(args[num])
#define GET_PTR_ARG(num, type) ToolKit::GetInner<type>(args[num])
#define ARGS(...) std::vector<BaseType::Object*>({__VA_ARGS__})
#define CALC(OBJECT, NAME, ...) Runtime::VM::Calc(OBJECT->getAttr(#NAME), ARGS(__VA_ARGS__))

#endif
