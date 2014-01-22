#ifndef ST_7834298472_AST_XLIST
#define ST_7834298472_AST_XLIST
#include "AST.h"
#include <vector>
#include <string>
namespace AST
{
    class Expr;
    class LValue;
    class Stmt;
    template <class T>
    class XList : public AST {
    public:
        std::vector<T> list;
        static void FillVector(XList* src, std::vector<T>& dst) {src->list.swap(dst); delete src;}
        XList() : AST(Location()) {}
        XList(T s1) : AST(Location()), list(1, s1) {}
        XList(XList* left, T right) : AST(Location()) {FillVector(left, list); list.push_back(right);}
    };
    typedef XList<std::string> IDList;
    typedef XList<Expr*> ExprList;
    typedef XList<LValue*> LValueList;
    typedef XList<Stmt*> StmtList;
}
#endif
