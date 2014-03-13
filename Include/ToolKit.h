#ifndef ST_9834721029_TOOLKIT
#define ST_9834721029_TOOLKIT
#include "BaseType/BuiltinFunc.h"
#include "BaseType/PtrObject.h"
#include "BaseType/Excpt.h"
#include "BaseType/State.h"
#include "BuiltinType/Null.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/Double.h"
#include "BuiltinType/Bool.h"
#include "BuiltinType/String.h"
#include "Exception.h"
namespace ToolKit {
    template <class T>
    inline T* SafeConvert(BaseType::Object* t) {
        T* ret = dynamic_cast<T*>(t);
        if (!ret) {
            ST_RAISE(VM, {{"__state__", BaseType::Excpt::ConvertError}});
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
    template <class T, typename... Args>
    inline pObject CreateObj(const pObject& state, Args... args) {
        pObject ret = new BaseType::Object(state);
        typedef typename std::remove_reference<T>::type _T;
        ret["__inner__"] = new BaseType::PtrObject<_T>(new _T(args...));
        return std::move(ret);
    }
    static pObject& null = BuiltinType::Null::Obj;
}
template <class T>
inline T& BaseType::pObjects::pObjectBase::To() const {
    return *ToolKit::SafeConvert<BaseType::PtrObject<T>>(GetPtr()->getAttr("__inner__").GetPtr())->ptr;
}
template <typename T, typename... Arg>
void BaseType::pObjects::pObjectBase::SetObj(Arg... args) const {
    typedef typename std::remove_reference<T>::type _T;
    GetPtr()->setAttr("__inner__", new BaseType::PtrObject<_T>(new _T(args...)));
}
#define ST_ARG_ERROR ST_RAISE(VM, {{"__state__", BaseType::Excpt::ArgCountError}})
#define ST_CHECK_ARG_SIZE(CONDITION) do {if (!(args.size() CONDITION)) {ST_ARG_ERROR;}} while(0)
#define ST_GET_ARG(num) args[num]
#define ST_GET_PTR_ARG(num, type) (args[num].To<type>())
#define ST_GET_ARG_STATE(num) (args[num]->getAttr("__state__"))
#define ST_FUNC(Block, ...) (new BaseType::BuiltinFunc([__VA_ARGS__](const std::vector<pObject>& args) ->pObject {Block return ToolKit::null;}))
#define ST_FUNC_ARG(ARG_SIZE, Block, ...) ST_FUNC({ST_CHECK_ARG_SIZE(ARG_SIZE); Block})
#define ST_TO(OBJ, CLASS) ((OBJ).To<BuiltinType::CLASS::Inner>())

#endif

