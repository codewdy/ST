#ifndef ST_81723i8126_STC_GETATTR
#define ST_81723i8126_STC_GETATTR
#include "STC.h"
#include <string>

namespace STC {
    /**get a attribute from the top of stack.*/
    class GetAttr : public STC {
    public:
        std::string str;///<the attribute.
        GetAttr(std::string _str) : STC(STC::GetAttr), str(_str) {}
    };
}
#endif
