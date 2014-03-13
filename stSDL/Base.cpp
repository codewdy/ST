#include "stSDL.h"
namespace stSDL {
    pObject Base;
    void InitBase() {
            Base = new BaseType::State();
            Base["onLeftClick"] = ST_FUNC_ARG(==2, {
                return ToolKit::null;
            });
            Base["onRightClick"] = ST_FUNC_ARG(==2, {
                return ToolKit::null;
            });
            Base["onKeyDown"] = ST_FUNC_ARG(==1, {
                return ToolKit::null;
            });
            Base["onKeyUp"] = ST_FUNC_ARG(==1, {
                return ToolKit::null;
            });
            Base["onRedraw"] = ST_FUNC_ARG(==2, {
                return ToolKit::null;
            });
            Base["onQuit"] = ST_FUNC_ARG(==1, {
                return true;
            });
            Base["width"] = 640;
            Base["height"] = 480;
            Base["title"] = "Noname";
    }
}
