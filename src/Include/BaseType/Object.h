#ifndef ST_7832901289_BASETYPE_OBJECT
#define ST_7832901289_BASETYPE_OBJECT
#include <unordered_map>
#include <string>
#include "ObjPtr.h"
#include "DefState.h"

namespace BaseType {
    /**the Base state of all state.*/
    class Object {
        Object(const Object&);
        Object& operator==(const Object&);
    public:
        /**the dict of this object.*/
        std::unordered_map<std::string, ObjPtr> dict;
        Object(Object* state = StateObject);
        /**get Attribute from dict or state, other state can override it.*/
        virtual Object* getAttr(std::string attr);
        /**get Attribute from dict or state, other state can override it.*/
        virtual void setAttr(std::string attr, Object* obj);
        virtual ~Object();
    };
}
#endif
