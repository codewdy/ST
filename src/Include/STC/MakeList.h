#ifndef ST_1987237812_STC_MAKELIST
#define ST_1987237812_STC_MAKELIST
#include "STC.h"

namespace STC {
    /**Make A List for the top num element of stack.*/
    class MakeList : public STC {
    public:
        int num;///<the length of the list.
        MakeList(int _num) : STC(STC::MakeList), num(_num) {}
    };
}
#endif
