#ifndef ST_7812365712_STC_POP
#define ST_7812365712_STC_POP
#include "STC.h"

namespace STC {
    /**Just Pop.*/
    class Pop : public STC {
    public:
        int num;///<Pop num elements at once.
        Pop(int _num = 1) : STC(STC::Pop), num(_num) {}
    };
}
#endif
