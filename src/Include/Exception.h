#ifndef ST_8932849283_Exception_Exception
#define ST_8932849283_Exception_Exception
#include <string>
#include <iostream>
#include "AST/AST.h"
#include "BaseType/pObject.h"
namespace Exception {
    extern std::ostream* LogFile;
    class Exception {};
#define DEFEXCPTION(CLASS) class CLASS##Exception : public Exception {};
    class LocException : public Exception {
    public:
        std::string filename;
        int lineno;
        LocException(AST::Location _loc) : filename(*_loc.str), lineno(_loc.lineno) {}
        LocException(const std::string& _filename, int _lineno) : filename(_filename), lineno(_lineno) {}
        LocException(std::string&& _filename = "", int _lineno = -1) : filename(std::move(_filename)), lineno(_lineno) {}
    };
#define DEFLOCEXCPTION(CLASS) class CLASS##Exception : public LocException {public: using LocException::LocException;};
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

    DEFEXCPTION(NotImplement)
    DEFEXCPTION(DoubleFault)
    DEFLOCEXCPTION(Break)
    DEFLOCEXCPTION(Syntax)

#undef DEFEXCPTION
#undef DEFLOCEXCPTION
}

#ifdef DEBUG
#define Raise(TYPE, ...) do{\
    Exception::TYPE##Exception ex = Exception::TYPE##Exception(__VA_ARGS__);\
    *(Exception::LogFile) << "Exception[" << #TYPE << "Exception] Raise At " << __FILE__ << ":" << __LINE__ << std::endl;\
    throw ex;\
}while(0)
#else
#define Raise(TYPE, ...) do{\
    Exception::TYPE##Exception ex = Exception::TYPE##Exception(__VA_ARGS__);\
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

