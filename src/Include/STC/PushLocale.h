#ifndef ST_7389426213_STC_PUSHLOCALE
#define ST_7389426213_STC_PUSHLOCALE
#include "STC.h"

namespace STC {
    /**Push A Locale Expr to the stack.*/
    class PushLocale : public STC {
    public:
        PushLocale() : STC(STC::PushLocale) {}
    };
}
#endif
