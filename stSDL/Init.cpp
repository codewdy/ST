#include <ST/ToolKit.h>
#include "stSDL.h"

namespace stSDL {
    SDL_Window* gWindow;
    SDL_Surface* gSurface;
    Uint32 RedrawEvent;

    void InitState() {
        if (Base.ref_equal(nullptr))
            return;
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
        Base["onRedraw"] = ST_FUNC_ARG(==1, {
            return ToolKit::null;
        });
        Drawer = new BaseType::State();
        Drawer["DrawLine"] = ST_FUNC_ARG(==4, {
            //TODO
        });
        Run = SDL_RUN;
    }
    extern "C"
    void Init(const pObject& nmspace) {
        InitState();
        nmspace["Base"] = Base;
        nmspace["Drawer"] = Drawer;
        nmspace["Run"] = Run;
    }
}

