#ifndef ST_3727312637_AST_IDS
#define ST_3727312637_AST_IDS
#include "AST.h"
namespace AST
{
    class Identifier;
    class Oper;
    class IDs : public AST
    {
    protected:
        IDs();
        IDs(const IDs&);
    public:
        static IDs* Create();
        static IDs* Create(Identifier* s1);
        static IDs* Create(IDs* s1, Oper* s2, Identifier* s3);
    };
}
#endif

