#include "ToolKit.h"
#include "BaseType/Namespace.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Init.h"
#include "BaseType/Init.h"
#include "BaseType/Import.h"
#include "Runtime/VM.h"
#include <dlfcn.h>

namespace BaseType {
    ST_DEF_FUNC(Import) {
        ST_CHECK_ARG_SIZE(==1);
        pObject ret = Runtime::VM::CreateGlobal();
        std::string filename = ST_GET_PTR_ARG(0, BuiltinType::String::Inner);
        if (filename.substr(filename.size() - 3, 3) == ".st") {
            //TODO
        } else {
            void* op = dlopen(filename.c_str(), RTLD_NOW);
            if (op == nullptr) {
                //TODO
            }
            std::cout << op << std::endl;
            std::cout << dlerror() << std::endl;
            typedef void (*CInit)(const pObject& obj);
            CInit init = (CInit)dlsym(op, "Init");
            init(ret);
        }
        return ret;
    }
}
