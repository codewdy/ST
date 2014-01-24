#ifndef ST_3894281273_STC_CALL
#define ST_3894281273_STC_CALL
#include "STC.h"

namespace STC {
    /**call the top, and give some parms(high->low==left->right), push the return to top.*/
    class Call : public STC {
    public:
        unsigned int parmCount;
        Call(unsigned int _parmCount) : STC(STC::Call), parmCount(_parmCount) {}
    };
}
#endif
