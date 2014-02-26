#ifndef ST_SDL_9823871982_SDL
#define ST_SDL_9823871982_SDL
#include <ST/ToolKit.h>
#include <SDL2/SDL.h>
namespace stSDL {
    extern pObject Base;
    extern pObject Drawer;
    extern pObject Run;
    extern SDL_Window* gWindow;
    extern SDL_Surface* gSurface;
    extern Uint32 RedrawEvent;
    ST_DEF_FUNC(SDL_Run);
    extern "C"
    void Init(const pObject& nmspace);
}
#endif

