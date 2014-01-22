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
    class XList {
    public:
        std::vector<T> list;
        static void FillVector(XList* src, std::vector<T>& dst) {src->list.swap(dst); delete src;}
        XList() {}
        XList(T s1) : list(1, s1) {}
        XList(XList* left, T right) {FillVector(left, list); list.push_back(right);}
    };

    template <class T>
    class PXList {
    public:
        std::vector<T*> list;
        static void FillVector(PXList* src, std::vector<T*>& dst) {src->list.swap(dst); delete src;}
        PXList() {}
        PXList(T* s1) : list(1, s1) {}
        PXList(PXList* left, T* right) {FillVector(left, list); list.push_back(right);}
        ~PXList() {
            for (auto item : list)
                delete item;
        }
    };

    typedef XList<std::string> IDList;
    typedef PXList<Expr> ExprList;
    typedef PXList<LValue> LValueList;
    typedef PXList<Stmt> StmtList;
}
#endif
