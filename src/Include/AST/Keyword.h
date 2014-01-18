#ifndef ST_8263748190_AST_KEYWORD
#define ST_8263748190_AST_KEYWORD
#include "AST.h"
namespace AST
{
    class Keyword : public AST
    {
    public:
        enum Type {
            IF,
            ELSE,
            FUNC,
            STATE,
            FOR,
            WHILE,
            BREAK
        };
        Keyword(Location _loc, Type _type);
    };
}
#endif

