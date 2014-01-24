#ifndef ST_7568251236_STC_PUSHINTEGER
#define ST_7568251236_STC_PUSHINTEGER
#include "STC.h"
#include <string>

namespace STC {
    /**Push a integer literal to the stack.*/
    class PushInteger : public STC {
    public:
        std::string str;///<the literal.
        PushInteger(std::string _str) : STC(STC::PushInteger), str(_str) {}
    };
}
#endif
