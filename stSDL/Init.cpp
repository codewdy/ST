#include <ST/ToolKit.h>
#include "stSDL.h"
#include <SDL2/SDL_image.h>

namespace stSDL {
    pObject Base;
    pObject Drawer;
    pObject Run;
    pObject Surface;
    pObject LoadImage;
    SDL_Window* gWindow;
    SDL_Surface* gSurface;
    Uint32 RedrawEvent;

    void InitState() {
        if (!Base.ref_equal(nullptr))
            return;
        const int imgFlags = IMG_INIT_PNG || IMG_INIT_JPG || IMG_INIT_TIF;
        if (IMG_Init(imgFlags) != imgFlags) {
            //TODO
        }
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            //TODO
        }
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
        Base["onQuit"] = ST_FUNC_ARG(==1, {
            return true;
        });
        Drawer = new BaseType::State();
        Drawer["DrawLine"] = ST_FUNC_ARG(==4, {
            //TODO
        });
        Run = SDL_Run;
        Surface = new BaseType::State();
        Surface["__init__"] = ST_FUNC_ARG(==2, {
            args[0].SetObj<Surface_t>(IMG_Load(args[1]["__str__"]().To<std::string>().c_str()));
        });
        LoadImage = ST_FUNC_ARG(==1, {
            std::string fn = args[0]["__str__"]().To<std::string>();
        });
    }
    extern "C"
    void Init(const pObject& nmspace) {
        InitState();
        nmspace["Base"] = Base;
        nmspace["Drawer"] = Drawer;
        nmspace["Run"] = Run;
    }
}

