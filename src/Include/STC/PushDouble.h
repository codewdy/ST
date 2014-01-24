#ifndef ST_8924267345_STC_PUSHDOUBLE
#define ST_8924267345_STC_PUSHDOUBLE
#include "STC.h"
#include <string>

namespace STC {
    /**Push A Double Literal To Stack.*/
    class PushDouble : public STC {
    public:
        std::string str;///<The double literal.
        PushDouble(std::string _str) : STC(STC::PushDouble), str(_str) {}
    };
}
#endif
