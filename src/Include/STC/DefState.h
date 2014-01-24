#ifndef ST_2389168243_STC_DEFFUNC
#define ST_2389168243_STC_DEFFUNC
#include "STC.h"

namespace STC {
    /**Def A State, code would run immediately when reach this code.*/
    class DefState : public STC {
    public:
        STC* code;///<goto code.
        DefState(STC* _code = 0) : STC(STC::DefState), code(_code) {}
    };
}
#endif
