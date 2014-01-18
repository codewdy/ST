#ifndef ST_8236941704_AST_IDENTIFIER
#define ST_8236941704_AST_IDENTIFIER
#include "AST.h"
namespace AST
{
    class Identifier : public AST
    {
    public:
        Identifier(Location _loc, const char* str);
    };
}
#endif

