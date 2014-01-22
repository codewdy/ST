#ifndef ST_7834298472_AST_IDLIST
#define ST_7834298472_AST_IDLIST
#include "AST.h"
#include <vector>
#include <string>
namespace AST
{
    class IDList : public AST
    {
    protected:
        IDList(const IDList&);
    public:
        std::vector<std::string> exprs;
        IDList(Location _loc) : AST(_loc) {}
        IDList(Location _loc, std::string s1) : AST(_loc), exprs()
        static IDList* Create(IDList* left, std::string right);
        static void FillVector(IDList* src, std::vector<std::string>& dst);
    };
}
#endif
