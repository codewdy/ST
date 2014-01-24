#ifndef ST_8197236782_STC_PUSHGLOBAL
#define ST_8197236782_STC_PUSHGLOBAL
#include "STC.h"

namespace STC {
    /**Push the Global Expr to thje stack.*/
    class PushGlobal : public STC {
    public:
        PushGlobal() : STC(STC::PushGlobal) {}
    };
}
#endif
