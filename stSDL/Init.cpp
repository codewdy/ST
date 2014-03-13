#include <ST/ToolKit.h>
#include "stSDL.h"
#include <SDL2/SDL_image.h>

namespace stSDL {
    SDL_Window* gWindow;
    SDL_Surface* gSurface;
    SDL_Renderer* gRender;

#define INIT(CLASS) void Init##CLASS();Init##CLASS();
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
        INIT(Base);
        INIT(Drawer);
        INIT(Surface);
        INIT(Run);
    }
    extern "C"
    void Init(const pObject& nmspace) {
        InitState();
        nmspace["Base"] = Base;
        nmspace["Drawer"] = Drawer;
        nmspace["Run"] = Run;
        nmspace["Surface"] = Surface;
        nmspace["ReDraw"] = ReDraw;
        nmspace["Rect"] = Rect;
    }
}

