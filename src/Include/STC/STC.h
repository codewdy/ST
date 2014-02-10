#ifndef ST_7392819203_STC_STC
#define ST_7392819203_STC_STC

#include <vector>
#include <string>
#include <unordered_map>

#define ALL_STC_DEF\
    NONEARG(CopyTop)\
    NONEARG(PushLocale)\
    NONEARG(PushGlobal)\
    NONEARG(PushNull)\
    STRINGARG(PushString)\
    STRINGARG(PushInteger)\
    STRINGARG(PushDouble)\
    STRINGARG(GetAttr)\
    STRINGARG(SetAttr)\
    GOTOARG(Goto)\
    GOTOARG(TrueGoto)\
    GOTOARG(FalseGoto)\
    INTARG(Call)\
    NONEARG(Return)\
    INTARG(MakeList)\
    STRINGARG(FuncArg)\
    BLOCKARG(DefFunc)\
    BLOCKARG(DefState)\
    NONEARG(Pop)\
    NONEARG(Nop)\
    STRINGARG(SourceFile)\
    INTARG(SourceLine)\
    GOTOARG(Try)\
    GOTOARG(Catch)

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
#define NONEARG(CLASS) CLASS,
#define STRINGARG(CLASS) CLASS,
#define INTARG(CLASS) CLASS,
#define GOTOARG(CLASS) CLASS,
#define BLOCKARG(CLASS) CLASS,
        ALL_STC_DEF
#undef NONEARG
#undef STRINGARG
#undef INTARG
#undef GOTOARG
#undef BLOCKARG
        } type; ///<The Type Of the STC.
        STC* code;
        int num;
        std::string str;
        static std::unordered_map<int, Arg> ArgMap;
        STC(Type _type) : next(nullptr), arg(ArgMap[_type]), type(_type) {}
        STC(Type _type, STC* _code) : next(nullptr), arg(ArgMap[_type]), type(_type), code(_code) {}
        STC(Type _type, int _num) : next(nullptr), arg(ArgMap[_type]), type(_type), num(_num) {}
        STC(Type _type, std::string _str) : next(nullptr), arg(ArgMap[_type]), type(_type), str(_str) {}

#define NONEARG(CLASS) static STC* Create##CLASS() {return new STC(CLASS);}
#define STRINGARG(CLASS) static STC* Create##CLASS(std::string _str) {return new STC(CLASS, _str);}
#define INTARG(CLASS) static STC* Create##CLASS(int _num) {return new STC(CLASS, _num);}
#define GOTOARG(CLASS) static STC* Create##CLASS(STC* _code = nullptr) {return new STC(CLASS, _code);}
#define BLOCKARG(CLASS) static STC* Create##CLASS(STC* _code = nullptr) {return new STC(CLASS, _code);}
        ALL_STC_DEF
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
        STCList() : beg(nullptr), end(nullptr) {}
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
