#ifndef ST_1892379128_STC_FALSEGOTO
#define ST_1892379128_STC_FALSEGOTO
#include "STC.h"

namespace STC {
    /**Test & Pop the top of the stack, if 0, goto code.*/
    class FalseGoto : public STC {
    public:
        STC* code;///<goto code.
        FalseGoto(STC* _code = 0) : STC(STC::FalseGoto), code(_code) {}
    };
}
#endif
