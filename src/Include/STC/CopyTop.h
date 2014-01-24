#ifndef ST_8737189137_STC_COPYTOP
#define ST_8737189137_STC_COPYTOP
#include "STC.h"

namespace STC {
    /**Copy the top of the stack and push it.*/
    class CopyTop : public STC {
    public:
        CopyTop() : STC(STC::CopyTop) {}
    };
}
#endif
