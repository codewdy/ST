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
        /**the filename Current STC from.*/
        std::string SourceFile;
        /**the line Current STC from.*/
        int SourceLine;
        /**The Size of the ObjectStack whe enter this Context.*/
        int ObjSize;
        Context(const pObject& _Global, pObject&& _Locale, STC::STC* _code) : Global(_Global), Locale(std::move(_Locale)), code(_code) {}
        Context(const pObject& _Global, const pObject& _Locale, STC::STC* _code) : Global(_Global), Locale(std::move(_Locale)), code(_code) {}
    };
}
#endif
