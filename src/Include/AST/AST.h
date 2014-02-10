#ifndef ST_7394856291_AST_AST
#define ST_7394856291_AST_AST
#include <memory>
#include <string>
#include <vector>

namespace AST {
    class Visitor;
    /**Location Of Source.*/
    struct Location {
        std::string* str;///<Source File Name.
        int lineno;///<Source Line Number.
        Location(std::string* _str = nullptr, int _lineno = 0) : str(_str), lineno(_lineno) {}
    };
    /**Base class for AST.*/
    class AST {
        AST(const AST&);///<Just Disable Copy.
        AST& operator= (const AST&);///<Just Disable Copy.
    protected:
        AST(Location _loc) : loc(_loc) {}
    public:
        Location loc;///<Location Reported When ST_RAISE Error.
        /**Visitor Pattern Interface.
         * Visitor would call this method to decide which the visitor should do.*/
        virtual void visit(Visitor* that) = 0;
        virtual ~AST();
    };
}
#endif

