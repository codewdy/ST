#ifndef ST_7482647236_AST_DOUBLE
#define ST_7482647236_AST_DOUBLE
#include "Expr.h"
#include <string>
namespace AST {
    /**AST for Double Literal.*/
    class Double : public Expr {
    public:
        std::string str;///<Double Inner Str
        Double(Location _loc, std::string _str) : Expr(_loc), str(_str) {}
        void visit(Visitor* v);
    };
}
#endif

