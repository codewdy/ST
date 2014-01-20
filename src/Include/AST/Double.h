#ifndef ST_7482647236_AST_DOUBLE
#define ST_7482647236_AST_DOUBLE
#include "Expr.h"
#include <string>
namespace AST {
    class Double : public Expr {
    public:
        std::string str;
        Double(Location _loc, std::string _str);
        void visit(Visitor* v);
    };
}
#endif

