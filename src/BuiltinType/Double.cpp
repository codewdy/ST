#include "BuiltinType/Double.h"
#include "BuiltinType/String.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"
#include <iostream>
#include <sstream>

namespace BuiltinType {
    namespace Double {
        BaseType::ObjPtr STATE;

        BaseType::Object* Create(std::string str) {
            std::stringstream in(str);
            Inner red;
            in >> red;
            if (!in) {
                //TODO: Add an exception.
            }
            return Create(red);
        }

        BaseType::Object* Create(Inner num) {
            BaseType::Object* ret = new BaseType::PtrObject<Inner>(new Inner(num), STATE);
            return ret;
        }

        void InitState() {
            if ((BaseType::Object*)STATE)
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            STATE->setAttr("__add__", new BaseType::BuiltinFunc(__add__));
            STATE->setAttr("__minus__", new BaseType::BuiltinFunc(__minus__));
            STATE->setAttr("__mul__", new BaseType::BuiltinFunc(__mul__));
            STATE->setAttr("__div__", new BaseType::BuiltinFunc(__div__));
            STATE->setAttr("__str__", new BaseType::BuiltinFunc(__str__));
        }

        DEF_OPER(__add__, +)
        DEF_OPER(__minus__, -)
        DEF_OPER(__mul__, *)
        DEF_OPER(__div__, /)

        DEF_BUILTIN_FUNC(__str__) {
            CHECK_ARG_SIZE(==1);
            std::ostringstream ret;
            ret << GET_PTR_ARG(0, Inner);
            return String::Create(ret.str());
        }
    }
}

