#ifndef ST_8932849283_Exception_Exception
#define ST_8932849283_Exception_Exception
#include <string>
#include <iostream>
#include "AST/AST.h"
#include "BaseType/pObject.h"
namespace Exception {
    extern std::ostream* LogFile;
    class Exception {};
#define ST_DEF_EXCPTION(CLASS) class CLASS##Exception : public Exception {};
    class LocException : public Exception {
    public:
        std::string filename;
        int lineno;
        LocException(AST::Location _loc) : filename(*_loc.str), lineno(_loc.lineno) {}
        LocException(const std::string& _filename, int _lineno) : filename(_filename), lineno(_lineno) {}
        LocException(std::string&& _filename = "", int _lineno = -1) : filename(std::move(_filename)), lineno(_lineno) {}
    };
#define ST_DEF_LOC_EXCPTION(CLASS) class CLASS##Exception : public LocException {public: using LocException::LocException;};
    class VMException : public Exception {
    public:
        pObject excpt;
        struct Trace {
            std::string filename;
            int lineno;
        };
        std::vector<Trace> trace;
        VMException(pObject&& _excpt) : excpt(std::move(_excpt)) {}
        VMException(const pObject& _excpt) : excpt(_excpt) {}
        void print(std::ostream& out);
    };

    ST_DEF_EXCPTION(NotImplement)
    ST_DEF_EXCPTION(DoubleFault)
    ST_DEF_LOC_EXCPTION(Break)
    ST_DEF_LOC_EXCPTION(Syntax)

#undef ST_DEF_EXCPTION
#undef ST_DEF_LOC_EXCPTION
}

#ifdef DEBUG
#define ST_RAISE(TYPE, ...) do{\
    Exception::TYPE##Exception ex = Exception::TYPE##Exception(__VA_ARGS__);\
    *(Exception::LogFile) << "Exception[" << #TYPE << "Exception] Raise At " << __FILE__ << ":" << __LINE__ << std::endl;\
    throw ex;\
}while(0)
#else
#define ST_RAISE(TYPE, ...) do{\
    Exception::TYPE##Exception ex = Exception::TYPE##Exception(__VA_ARGS__);\
    throw ex;\
}while(0)
#endif

#ifdef DEBUG
#define ST_WARN(ST_WARNing) do{\
    *(Exception::LogFile) << "Waring at " << __FILE__ << "." << __LINE__ \
        << ":" << ST_WARNing << std::endl;\
}while(0)
#else
#define ST_WARN(ST_WARNing) do{}while(0)
#endif

#endif

