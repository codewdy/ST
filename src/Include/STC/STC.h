#ifndef ST_7392819203_STC_STC
#define ST_7392819203_STC_STC

#include <vector>

/**STC is a stack-base code.*/
namespace STC {
    class STC;

    /**STC Code Base Class.*/
    class STC {
    public:
        /**Temp Var On Runtime without name.*/
        typedef unsigned int Var;
        /**Temp Label For jump.*/
        typedef STC* Label;
        static const Var Global = 0;
        static const Var Locale = 1;
        /**A Link List Of STC.*/
        STC* next;
        enum Type {
            CopyTop, PushLocale, PushGlobal, PushString, PushInteger, PushDouble, GetAttr, SetAttr, Goto, TrueGoto, FalseGoto, Call, MakeList, DefFunc, DefState, Pop, Nop
        } type; ///<The Type Of the STC.
        STC(Type _type) : next(0), type(_type) {}
    };

    /**STC 's Link List.*/
    struct STCList {
        STC* beg;
        STC* end;
        STCList() : beg(0), end(0) {}
        STCList(STC* _lst) : beg(_lst), end(_lst) {}
        /**Append lst to next.*/
        STCList& Append(const STCList lst) {
            if (beg) {
                end->next = lst.beg;
                end = lst.end;
            } else {
                beg = lst.beg;
                end = lst.end;
            }
            return *this;
        }
    };
}
#endif
