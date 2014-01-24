#ifndef ST_2783646287_STC_NOP
#define ST_2783646287_STC_NOP
#include "STC.h"

namespace STC {
    /**Just Ignore.*/
    class Nop : public STC {
    public:
        Nop() : STC(STC::Nop) {}
    };
}
#endif
