#ifndef ST_1982738912_RUNTIME_CONTEXT
#define ST_1982738912_RUNTIME_CONTEXT

#include "BaseType/ObjPtr.h"
#include "STC/STC.h"
namespace Runtime {
    /**A class for the function runtime context.*/
    class Context {
    public:
        /**For Global Expr Return.*/
        BaseType::ObjPtr Global;
        /**For Locale Expr Return.*/
        BaseType::ObjPtr Locale;
        /**STC For the Code Running.*/
        STC::STC* code;
        Context(BaseType::Object* _Global, BaseType::Object* _Locale, STC::STC* _code) : Global(_Global), Locale(_Locale), code(_code) {}
    };
}
#endif
