#ifndef ST_7394856291_AST_AST
#define ST_7394856291_AST_AST
#include <memory>
#include <string>
#include <vector>

namespace AST {
    extern std::vector<std::string> source;
    extern std::string* currentSource;
    class Visitor;
    struct Location {
        std::string* str;
        std::size_t lineno;
    };
    class AST;
    typedef std::shared_ptr<AST> Tree;
    typedef AST* Node;
    class AST {
    public:
        Location loc;
        AST(Location _loc);
        virtual void visit(Visitor* that); 
        virtual ~AST();
    };
}
#endif

