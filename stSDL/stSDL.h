#ifndef ST_SDL_9823871982_SDL
#define ST_SDL_9823871982_SDL
#include <ST/ToolKit.h>
#include <SDL2/SDL.h>
namespace stSDL {
    extern pObject Base;
    extern pObject Drawer;
    extern pObject Run;
    ST_DEF_FUNC(SDL_RUN);
    extern "C"
    void Init(const pObject& nmspace);
    extern SDL_Window* gWindow;
    extern SDL_Surface* gSurface;
    extern Uint32 RedrawEvent;
}
#endif

