#ifndef ST_8928319384_BASETYPE_DICT
#define ST_8928319384_BASETYPE_DICT

#include "Object.h"
#include <unordered_map>

namespace BaseType {
    class Dict : public Object {
    public:
        std::unordered_map<std::string, pObject> dict;
        pObject getElement(const std::string& index);
        void setElement(const std::string& index, pObject obj);
    };
}
#endif
