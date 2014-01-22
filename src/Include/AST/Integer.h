#ifndef ST_2873292179_AST_INTEGER
#define ST_2873292179_AST_INTEGER
#include "Expr.h"
#include <string>
namespace AST {
    class Integer : public Expr {
    public:
        std::string str;
        Integer(Location _loc, std::string _str) : Expr(_loc), str(_str) {}
        void visit(Visitor* v);
    };
}
#endif

