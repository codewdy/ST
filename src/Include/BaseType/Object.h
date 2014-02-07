#ifndef ST_7832901289_BASETYPE_OBJECT
#define ST_7832901289_BASETYPE_OBJECT
#include <unordered_map>
#include <string>
#include "GC.h"

namespace BaseType {
    /**the Base state of all state.*/
    class Object {
        Object(const Object&) = delete;
        Object& operator==(const Object&) = delete;
    public:
        static pObject STATE;
        /**the dict of this object.*/
        std::unordered_map<std::string, pObjectExt> dict;
        Object(const pObject& state = STATE);
        /**get Attribue from dict or state, this will return 0 when not found, other state can override it.*/
        virtual Object* _getAttr(const std::string& attr);
        /**get Attribute from dict or state, other state can override it.*/
        virtual void _setAttr(const std::string& attr, Object* obj);
        /**get Attribute, this will raise an exception when not found.*/
        pObject getAttr(const std::string& attr) {
            Object* ret = _getAttr(attr);
            if (ret)
                return ret;
            else
                //TODO: Add an exception.
                throw "attr not found";
        }
        /**set a attribute, the same as _setattribute.*/
        void setAttr(const std::string& attr, const pObject& obj) {
            _setAttr(attr, obj);
        }
        virtual ~Object();
    };
}
#endif

