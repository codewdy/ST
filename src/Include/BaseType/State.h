#ifndef ST_8937289123_BASETYPE_STATE
#define ST_8937289123_BASETYPE_STATE

#include "Object.h"

namespace BaseType {
    class State : public Object {
    public:
        virtual pObject getAttr(std::string attr);
        virtual void setAttr(std::string attr, pObject obj);
    };
}
#endif
