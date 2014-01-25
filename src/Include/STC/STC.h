#ifndef ST_7392819203_STC_STC
#define ST_7392819203_STC_STC

#include <vector>
#include <string>
#include <unordered_map>

/**STC is a stack-base code.*/
namespace STC {
    /**STC Code Base Class.*/
    struct STC {
        /**Temp Label For jump.*/
        typedef STC* Label;
        /**A Link List Of STC.*/
        STC* next;
        enum Arg {
            NoneArg, StringArg, IntArg, GotoArg, BlockArg
        } arg;
        enum Type {
            CopyTop, PushLocale, PushGlobal, PushString, PushInteger, PushDouble, GetAttr, SetAttr, 
            Goto, TrueGoto, FalseGoto, Call, Return, MakeList, DefFunc, DefState, Pop, Nop
        } type; ///<The Type Of the STC.
        STC* code;
        int num;
        std::string str;
        static std::unordered_map<int, Arg> ArgMap;
        STC(Type _type) : next(0), arg(ArgMap[_type]), type(_type) {}
        STC(Type _type, STC* _code) : next(0), arg(ArgMap[_type]), type(_type), code(_code) {}
        STC(Type _type, int _num) : next(0), arg(ArgMap[_type]), type(_type), num(_num) {}
        STC(Type _type, std::string _str) : next(0), arg(ArgMap[_type]), type(_type), str(_str) {}
#define NONEARG(CLASS) static STC* Create##CLASS() {return new STC(CLASS);}
#define STRINGARG(CLASS) static STC* Create##CLASS(std::string _str) {return new STC(CLASS, _str);}
#define INTARG(CLASS) static STC* Create##CLASS(int _num) {return new STC(CLASS, _num);}
#define GOTOARG(CLASS) static STC* Create##CLASS(STC* _code = 0) {return new STC(CLASS, _code);}
#define BLOCKARG(CLASS) static STC* Create##CLASS(STC* _code = 0) {return new STC(CLASS, _code);}
        NONEARG(CopyTop)
        NONEARG(PushLocale)
        NONEARG(PushGlobal)
        STRINGARG(PushString)
        STRINGARG(PushInteger)
        STRINGARG(PushDouble)
        STRINGARG(GetAttr)
        STRINGARG(SetAttr)
        GOTOARG(Goto)
        GOTOARG(TrueGoto)
        GOTOARG(FalseGoto)
        INTARG(Call)
        NONEARG(Return)
        INTARG(MakeList)
        BLOCKARG(DefFunc)
        BLOCKARG(DefState)
        NONEARG(Pop)
        NONEARG(Nop)
#undef NONEARG
#undef STRINGARG
#undef INTARG
#undef GOTOARG
#undef BLOCKARG
    };
    
    /**STC 's Link List.*/
    struct STCList {
        STC* beg;
        STC* end;
        STCList() : beg(0), end(0) {}
        STCList(STC* _lst) : beg(_lst), end(_lst) {}
        /**Append lst to next.*/
        STCList& Append(STCList lst) {
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
