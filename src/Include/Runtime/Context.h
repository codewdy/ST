#ifndef ST_1982738912_RUNTIME_CONTEXT
#define ST_1982738912_RUNTIME_CONTEXT

#include "BaseType/Object.h"
#include "STC/STC.h"
namespace Runtime {
    /**A class for the function runtime context.*/
    class Context {
    public:
        /**For Global Expr Return.*/
        pObject Global;
        /**For Locale Expr Return.*/
        pObject Locale;
        /**STC For the Code Running.*/
        STC::STC* code;
        Context(const pObject& _Global, pObject&& _Locale, STC::STC* _code) : Global(_Global), Locale(std::move(_Locale)), code(_code) {}
    };
}
#endif
