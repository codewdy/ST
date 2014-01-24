#ifndef ST_1728361872_STC_DEFFUNC
#define ST_1728361872_STC_DEFFUNC
#include "STC.h"

namespace STC {
    /**Def A Func, code would not run in this STC Code.*/
    class DefFunc : public STC {
    public:
        STC* code;///<func code.
        DefFunc(STC* _code = 0) : STC(STC::Goto), code(_code) {}
    };
}
#endif
