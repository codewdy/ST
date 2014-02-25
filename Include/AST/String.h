#ifndef ST_2837461829_AST_STRING
#define ST_2837461829_AST_STRING
#include "Expr.h"
#include <string>
namespace AST {
    /**AST for String Literal.*/
    class String : public Expr {
    public:
        std::string str;///<Inner String.
        String(Location _loc, std::string _str) : Expr(_loc), str(_str) {}
        void visit(Visitor* v);
    };
}
#endif

