#ifndef ST_7832901289_BASETYPE_OBJECT
#define ST_7832901289_BASETYPE_OBJECT
#include <memory>
#include <vector>

namespace BaseType {
    class Dict;
    class Object;

    typedef std::shared_ptr<Object> pObject;

    class Object {
        Object(const Object&);
        Object& operator==(const Object&);
    public:
        Object();
        std::shared_ptr<Dict> dict;
        virtual pObject getAttr(std::string attr);
        virtual void setAttr(std::string attr, pObject obj);
        virtual ~Object();
    };
}
#endif
