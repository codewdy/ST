#ifndef ST_8236941704_AST_IDENTIFIER
#define ST_8236941704_AST_IDENTIFIER
#include "AST.h"
#include <string>
namespace AST
{
    class Identifier : public AST
    {
    public:
        Identifier(Location _loc, std::string str);
        void visit(Visitor* that);
    };
}
#endif

