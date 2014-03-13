#ifndef ST_SDL_9823871982_SDL
#define ST_SDL_9823871982_SDL
#include <ST/ToolKit.h>
#include <SDL2/SDL.h>
namespace stSDL {
    struct Surface_t {
        SDL_Surface* surf;
        SDL_Surface* operator->() {
            return surf;
        }
        SDL_Surface& operator*() {
            return *surf;
        }
        operator SDL_Surface*() {
            return surf;
        }
        Surface_t(SDL_Surface* _surf = nullptr) : surf(_surf) {}
        ~Surface_t() {
            SDL_FreeSurface(surf);
        }
    };
    extern pObject Base;
    extern pObject Drawer;
    extern pObject Run;
    extern pObject ReDraw;
    extern pObject Surface;
    extern pObject Rect;
    extern SDL_Window* gWindow;
    extern SDL_Surface* gSurface;
    extern SDL_Renderer* gRender;
    extern "C"
    void Init(const pObject& nmspace);
}
#endif

