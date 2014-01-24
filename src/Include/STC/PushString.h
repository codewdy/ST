#ifndef ST_8941287673_STC_PUSHSTRING
#define ST_8941287673_STC_PUSHSTRING
#include "STC.h"
#include <string>

namespace STC {
    /**Push A String Literal to the Stack.*/
    class PushString : public STC {
    public:
        std::string str;///<the string.
        PushString(std::string _str) : STC(STC::PushString), str(_str) {}
    };
}
#endif
