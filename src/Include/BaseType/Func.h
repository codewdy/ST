#ifndef ST_8329102910_BASETYPE_FUNC
#define ST_8329102910_BASETYPE_FUNC
#include "Object.h"

namespace BaseType {
    class Func : public Object {
    public:
        virtual pObject run(std::vector<pObject>) = 0;
    };
}

#endif
