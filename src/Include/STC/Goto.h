#ifndef ST_3489057398_STC_GOTO
#define ST_3489057398_STC_GOTO
#include "STC.h"

namespace STC {
    /**Jump To A Code without condition.*/
    class Goto : public STC {
    public:
        STC* code;///<goto code.
        Goto(STC* _code = 0) : STC(STC::Goto), code(_code) {}
    };
}
#endif
