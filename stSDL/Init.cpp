#include <ST/ToolKit.h>
#include "stSDL.h"
#include <SDL2/SDL_image.h>

namespace stSDL {
    pObject Base;
    pObject Drawer;
    pObject Run;
    pObject ReDraw;
    pObject Surface;
    SDL_Window* gWindow;
    SDL_Surface* gSurface;

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
        Base["width"] = 640;
        Base["height"] = 480;
        Base["title"] = "Noname";
        Drawer = new BaseType::State();
        Drawer["Draw"] = ST_FUNC_ARG(==1, {
            //TODO
            SDL_Surface* xx = args[0].To<Surface_t>();
            SDL_BlitSurface(args[0].To<Surface_t>(), NULL, gSurface, NULL);
        });
        Run = SDL_Run;
        Surface = new BaseType::State();
        Surface["__init__"] = ST_FUNC_ARG(==2, {
            std::string fn = args[1]["__str__"]().To<std::string>();
            args[0].SetObj<Surface_t>(IMG_Load(fn.c_str()));
            std::cout << args[0].GetPtr() << std::endl;
            return args[0];
        });
        ReDraw = ST_FUNC_ARG(==0, {
            SDL_Event e;
            e.type = SDL_WINDOWEVENT;
            e.window.windowID = SDL_GetWindowID(gWindow);
            e.window.event = SDL_WINDOWEVENT_EXPOSED;
            SDL_PushEvent(&e);
        });
    }
    extern "C"
    void Init(const pObject& nmspace) {
        InitState();
        nmspace["Base"] = Base;
        nmspace["Drawer"] = Drawer;
        nmspace["Run"] = Run;
        nmspace["Surface"] = Surface;
        nmspace["ReDraw"] = ReDraw;
    }
}

