#ifndef ST_8932849283_Exception_Exception
#define ST_8932849283_Exception_Exception
#include <string>
#include <iostream>
#include "AST/AST.h"
namespace Exception {
    extern std::ostream* LogFile;
    class Exception {};
#define DEFEXCPTION(CLASS) class CLASS##Exception : public Exception {};
    class LocException : public Exception {
    public:
        std::string filename;
        int lineno;
        LocException(AST::Location _loc) : filename(*_loc.str), lineno(_loc.lineno) {}
    };
#define DEFLOCEXCPTION(CLASS) class CLASS##Exception : public LocException {public: CLASS##Exception(AST::Location _loc) : LocException(_loc) {}};

    DEFEXCPTION(NotImplement)
    DEFLOCEXCPTION(Break)

#undef DEFEXCPTION
#undef DEFLOCEXCPTION
}

#ifdef DEBUG
#define Raise(TYPE, ...) do{\
    Exception::TYPE##Exception ex = Exception::TYPE##Excption(__VA_ARGS__);\
    *(Exception::LogFile) << "Exception[" << #TYPE << "Exception] Raise At " << __FILE__ << "." << __LINE__ << std::endl;\
    throw ex;\
}while(0)
#else
#define Raise(TYPE, ...) do{\
    Exception::TYPE##Exception ex = Exception::TYPE##Excption(__VA_ARGS__);\
    throw ex;\
}while(0)
#endif

#ifdef DEBUG
#define Warn(Warning) do{\
    Exception::LogFile << "Waring at " << __FILE__ << "." << __LINE__ \
        << ":" << Warning << std::endl;\
}while(0)
#else
#define Warn(Warning) do{}while(0)
#endif

#endif

