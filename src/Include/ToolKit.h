#ifndef ST_9834721029_TOOLKIT
#define ST_9834721029_TOOLKIT
#include "BaseType/BuiltinFunc.h"
#include "BaseType/PtrObject.h"
#define CHECK_ARG_SIZE(CONDITION) do {if (!(args.size() CONDITION)) {/*TODO:Add Exception.*/}} while(0)
namespace ToolKit {
    template <class T>
    inline T* SafeConvert(pObject t) {
        BaseType::Object* r = t;
        T* ret = dynamic_cast<T*>(r);
        if (!ret) {
            /*TODO:Add Exception.*/
        }
        return ret;
    }
    template <class T>
    inline T* SafeConvert(pObjectExt t) {
        BaseType::Object* r = t;
        T* ret = dynamic_cast<T*>(r);
        if (!ret) {
            /*TODO:Add Exception.*/
        }
        return ret;
    }
    template <class T>
    inline T& GetInner(const pObject& t) {
        return *SafeConvert<BaseType::PtrObject<T>>(t->getAttr("__inner__"))->ptr;
    }
    template <class T>
    inline pObject CreateObj(const pObject& state, const T& inner) {
        pObject ret = new BaseType::Object(state);
        typedef typename std::remove_reference<T>::type _T;
        ret->setAttr("__inner__", new BaseType::PtrObject<_T>(new _T(inner)));
        return std::move(ret);
    }
    template <class T>
    inline pObject CreateObj(const pObject& state, T&& inner) {
        pObject ret = new BaseType::Object(state);
        typedef typename std::remove_reference<T>::type _T;
        ret->setAttr("__inner__", new BaseType::PtrObject<_T>(new _T(std::move(inner))));
        return std::move(ret);
    }
    inline void SetFunc(const pObject& state, std::string&& name, BaseType::BuiltinFunc::pFunc t) {
        state->setAttr(std::move(name), new BaseType::BuiltinFunc(t));
    }
    inline BaseType::Object* GetOrigin(const pObject& p) {
        return p;
    }
    inline BaseType::Object* GetOrigin(const pObjectExt& p) {
        return p;
    }
}
#define GET_ARG(num) args[num]
#define GET_PTR_ARG(num, type) ToolKit::GetInner<type>(args[num])
#define GET_ARG_STATE(num) (args[num]->getAttr("__state__"))
#define ARGS(...) std::vector<pObject>({__VA_ARGS__})
#define CALC(OBJECT, NAME, ...) Runtime::VM::Calc(OBJECT->getAttr(#NAME), ARGS(__VA_ARGS__))
#define SET_FUNC(CLASS, FUNC) ToolKit::SetFunc(CLASS, #FUNC, FUNC)

#endif

