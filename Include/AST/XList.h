#ifndef ST_7834298472_AST_XLIST
#define ST_7834298472_AST_XLIST
#include "Expr.h"
#include "LValue.h"
#include "Stmt.h"
#include <vector>
#include <string>
namespace AST
{
    /**List For Something.*/ 
    template <class T>
    class XList {
    public:
        std::vector<T> list;
        /**Fill dst with src, then delete src.\warning src will be delete!*/
        static void FillVector(XList* src, std::vector<T>& dst) {src->list.swap(dst); delete src;}
        XList() {}
        XList(T s1) : list(1, s1) {}
        XList(XList* left, T right) {FillVector(left, list); list.push_back(right);}
        template <class T1> class Dest {public: static void destory(T1 x){}};
        template <class T1> class Dest<T1*> {public: static void destory(T1* x){delete x;}};
        ~XList() {
            for (auto item : list)
                Dest<T>::destory(item);
        }
    };

    typedef XList<std::string> IDList;
    typedef XList<Expr*> ExprList;
    typedef XList<Stmt*> StmtList;
}
#endif
