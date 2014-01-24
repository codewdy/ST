#ifndef ST_7842763487_STC_SETATTR
#define ST_7842763487_STC_SETATTR
#include "STC.h"
#include <string>

namespace STC {
    /**set the attribute of the top to the second top.*/
    class SetAttr : public STC {
    public:
        std::string str;///<the attribute.
        SetAttr(std::string _str) : STC(STC::SetAttr), str(_str) {}
    };
}
#endif
