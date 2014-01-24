#ifndef ST_7812934981_STC_TRUEGOTO
#define ST_7812934981_STC_TRUEGOTO
#include "STC.h"

namespace STC {
    /**Pop stack and test it, if not 0, goto code.*/
    class TrueGoto : public STC {
    public:
        STC* code;///<goto code.
        TrueGoto(STC* _code = 0) : STC(STC::TrueGoto), code(_code) {}
    };
}
#endif
