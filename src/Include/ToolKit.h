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
        return *SafeConvert<BaseType::PtrObject<T>>(t)->ptr;
    }
}
#define GET_ARG(num, type) ToolKit::SafeConvert<type>(args[num])
#define GET_PTR_ARG(num, type) (*GET_ARG(num, BaseType::PtrObject<type>)->ptr)

#endif
