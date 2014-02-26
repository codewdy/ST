#ifndef ST_7392819203_STC_STC
#define ST_7392819203_STC_STC

#include <vector>
#include <string>
#include <unordered_map>

#define ST_ALL_STC_DEF\
    ST_NONEARG(CopyTop)\
    ST_NONEARG(PushLocale)\
    ST_NONEARG(PushGlobal)\
    ST_NONEARG(PushNull)\
    ST_STRINGARG(PushString)\
    ST_STRINGARG(PushInteger)\
    ST_STRINGARG(PushDouble)\
    ST_NONEARG(PushObject)\
    ST_STRINGARG(GetAttr)\
    ST_STRINGARG(SetAttr)\
    ST_GOTOARG(Goto)\
    ST_GOTOARG(TrueGoto)\
    ST_GOTOARG(FalseGoto)\
    ST_INTARG(Call)\
    ST_NONEARG(Return)\
    ST_INTARG(MakeList)\
    ST_STRINGARG(FuncArg)\
    ST_BLOCKARG(DefFunc)\
    ST_BLOCKARG(DefState)\
    ST_NONEARG(Pop)\
    ST_NONEARG(Nop)\
    ST_STRINGARG(SourceFile)\
    ST_INTARG(SourceLine)\
    ST_GOTOARG(Try)\
    ST_GOTOARG(Catch)

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
#define ST_NONEARG(CLASS) CLASS,
#define ST_STRINGARG(CLASS) CLASS,
#define ST_INTARG(CLASS) CLASS,
#define ST_GOTOARG(CLASS) CLASS,
#define ST_BLOCKARG(CLASS) CLASS,
        ST_ALL_STC_DEF
#undef ST_NONEARG
#undef ST_STRINGARG
#undef ST_INTARG
#undef ST_GOTOARG
#undef ST_BLOCKARG
        } type; ///<The Type Of the STC.
        STC* code;
        int num;
        std::string str;
        static std::unordered_map<int, Arg> ArgMap;
        STC(Type _type) : next(nullptr), arg(ArgMap[_type]), type(_type) {}
        STC(Type _type, STC* _code) : next(nullptr), arg(ArgMap[_type]), type(_type), code(_code) {}
        STC(Type _type, int _num) : next(nullptr), arg(ArgMap[_type]), type(_type), num(_num) {}
        STC(Type _type, std::string _str) : next(nullptr), arg(ArgMap[_type]), type(_type), str(_str) {}

#define ST_NONEARG(CLASS) static STC* Create##CLASS() {return new STC(CLASS);}
#define ST_STRINGARG(CLASS) static STC* Create##CLASS(std::string _str) {return new STC(CLASS, _str);}
#define ST_INTARG(CLASS) static STC* Create##CLASS(int _num) {return new STC(CLASS, _num);}
#define ST_GOTOARG(CLASS) static STC* Create##CLASS(STC* _code = nullptr) {return new STC(CLASS, _code);}
#define ST_BLOCKARG(CLASS) static STC* Create##CLASS(STC* _code = nullptr) {return new STC(CLASS, _code);}
        ST_ALL_STC_DEF
#undef ST_NONEARG
#undef ST_STRINGARG
#undef ST_INTARG
#undef ST_GOTOARG
#undef ST_BLOCKARG
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
