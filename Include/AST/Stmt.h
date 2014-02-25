#ifndef ST_2836592813_AST_STMT
#define ST_2836592813_AST_STMT
#include "AST.h"
namespace AST
{
    /**AST for virtual Statement*/
    class Stmt : public AST
    {
    public:
        Stmt(Location _loc) : AST(_loc) {}
    };
}
#endif
