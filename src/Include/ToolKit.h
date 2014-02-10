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
    inline pObject CreateObj(const pObject& state, const T& inner) {
        pObject ret = new BaseType::Object(state);
        typedef typename std::remove_reference<T>::type _T;
        ret["__inner__"] = new BaseType::PtrObject<_T>(new _T(inner));
        return std::move(ret);
    }
    template <class T>
    inline pObject CreateObj(const pObject& state, T&& inner) {
        pObject ret = new BaseType::Object(state);
        typedef typename std::remove_reference<T>::type _T;
        ret["__inner__"] = new BaseType::PtrObject<_T>(new _T(std::move(inner)));
        return std::move(ret);
    }
    inline void SetFunc(const pObject& state, std::string&& name, BaseType::BuiltinFunc::pFunc t) {
        state[std::move(name)] = new BaseType::BuiltinFunc(t);
    }
    inline BaseType::Object* GetOrigin(const pObject& p) {
        return p.GetPtr();
    }
    inline BaseType::Object* GetOrigin(const pObjectExt& p) {
        return p.GetPtr();
    }
}
template <class T>
inline T& BaseType::pObjects::pObjectBase::To() const {
    return *ToolKit::SafeConvert<BaseType::PtrObject<T>>(GetPtr()->getAttr("__inner__").GetPtr())->ptr;
}
#define GET_ARG(num) args[num]
#define GET_PTR_ARG(num, type) (args[num].To<type>())
#define GET_ARG_STATE(num) (args[num]->getAttr("__state__"))
#define BUILTIN_FUNC_LAMBDA(Block, ...) (new BaseType::BuiltinFunc([__VA_ARGS__](const std::vector<pObject>& args) Block))
#define BUILTIN_FUNC_LAMBDA_ARG(ARG_SIZE, Block, ...)\
    (new BaseType::BuiltinFunc([__VA_ARGS__](const std::vector<pObject>& args) -> pObject {CHECK_ARG_SIZE(ARG_SIZE); Block}))

#endif

