#ifndef ST_8173265438_BASETYPE_PTROBJECT
#define ST_8173265438_BASETYPE_PTROBJECT

#include "Object.h"

namespace BaseType {
    extern ObjPtr PtrObjectSTATE;
    template<class T>
    class PtrObject : Object {
    public:
        T* ptr;
        PtrObject(T* _ptr) : Object(PtrObjectSTATE), ptr(_ptr) {}
        virtual ~PtrObject() {delete ptr;}
    };
}
#endif
