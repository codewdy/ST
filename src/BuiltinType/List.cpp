#include "BuiltinType/List.h"
#include "BuiltinType/String.h"
#include "BuiltinType/Integer.h"
#include "BuiltinType/Bool.h"
#include <sstream>
#include <iostream>
#include "BaseType/PtrObject.h"
#include "ToolKit.h"

namespace BuiltinType {
    namespace List {
        pObject STATE, IterSTATE;

        pObject Create(const InitInner& vars) {
            pObject ret = ToolKit::CreateObj(STATE, Inner());
            pObject in = ret["__inner__"];
            for (pObject item : vars)
                ret.To<Inner>().push_back(pObjectExt(item, in));
            return std::move(ret);
        }

        void InitState() {
            if (STATE.ref_not_equal(nullptr))
                return;
            STATE = new BaseType::State(BaseType::PtrObjectSTATE);
            IterSTATE = new BaseType::State;

            STATE["__add__"] = ST_FUNC_ARG(==2, {
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);
                Inner& rhs = ST_GET_PTR_ARG(1, Inner);
                InitInner ret(lhs.begin(), lhs.end());
                ret.insert(ret.end(), rhs.begin(), rhs.end());
                return std::move(ret);
            });

            STATE["__mul__"] = ST_FUNC_ARG(==2, {
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);
                int rhs = ST_GET_PTR_ARG(1, Integer::Inner);
                InitInner ret;
                for (int i = 0; i < rhs; i++)
                    ret.insert(ret.end(), lhs.begin(), lhs.end());
                return std::move(ret);
            });

            STATE["__get_element__"] = ST_FUNC_ARG(==2, {
                Inner& lhs = ST_GET_PTR_ARG(0, Inner);
                int rhs = ST_GET_PTR_ARG(1, Integer::Inner);
                if (lhs.size() <= rhs || rhs < 0) {
                    ST_RAISE(VM, {{"__state__", BaseType::Excpt::IndexError}});
                }
                return lhs[rhs];
            });

            STATE["__str__"] = ST_FUNC_ARG(==1, {
                Inner arg = ST_GET_PTR_ARG(0, Inner);
                String::Inner ret = "[";
                for (int i = 0; i < arg.size(); i++){
                    pObject str = arg[i]["__str__"]();
                    ret += str.To<String::Inner>();
                    if (i != arg.size() - 1)
                        ret += ", ";
                }
                ret += "]";
                return std::move(ret);
            });

            STATE["__iter__"] = ST_FUNC_ARG(==1, {
                pObject ret = new BaseType::Object(IterSTATE);
                ret["__array__"] = args[0];
                ret["__index__"] = 0;
                return std::move(ret);
            });

            IterSTATE["__next__"] = ST_FUNC_ARG(==1, {
                pObject ret = new BaseType::Object(IterSTATE);
                ret["__array__"] = args[0]["__array__"];
                Integer::Inner& idx = args[0]["__index__"].To<Integer::Inner>();
                ret["__index__"] = idx + 1;
                return std::move(ret);
            });

            IterSTATE["__is_end__"] = ST_FUNC_ARG(==1, {
                Inner arr = args[0]["__array__"].To<Inner>();
                Integer::Inner& idx = args[0]["__index__"].To<Integer::Inner>();
                return arr.size() <= idx;
            });

            IterSTATE["__get__"] = ST_FUNC_ARG(==1, {
                Inner arr = args[0]["__array__"].To<Inner>();
                Integer::Inner& idx = args[0]["__index__"].To<Integer::Inner>();
                if (arr.size() <= idx || idx < 0) {
                    ST_RAISE(VM, {{"__state__", BaseType::Excpt::IndexError}});
                }
                return arr[idx];
            });
        }
    }
}

