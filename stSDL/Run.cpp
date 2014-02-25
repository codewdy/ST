#include "stSDL.h"

namespace stSDL {
    static bool stSDL_Init(int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            return false;
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
        if (gWindow)
            return false;
        gSurface = SDL_GetWindowSurface(gWindow);
        return true;
    }
    static void stSDL_Release() {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
    ST_DEF_FUNC(SDL_Run) {
        if (stSDL_Init(640, 480)) {
            //TODO:Exception
        }
        SDL_Event event;
#define MOUSE_BUTTON_EVENT reinterpret_cast<SDL_MouseButtonEvent>(event)
#define KEYBOARD_EVENT reinterpret_cast<SDL_KeyboardEvent>(event)
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (MOUSE_BUTTON_EVENT.which == SDL_BUTTON_LEFT) {
                        args[0]["onLeftClick"](MOUSE_BUTTON_EVENT.x, MOUSE_BUTTON_EVENT.y);
                        break;
                    }
                    if (MOUSE_BUTTON_EVENT.which == SDL_BUTTON_RIGHT) {
                        args[0]["onRightClick"](MOUSE_BUTTON_EVENT.x, MOUSE_BUTTON_EVENT.y);
                        break;
                    }
                    break;
                case SDL_KEYDOWN:
                    args[0]["onKeyDown"](SDL_GetKeyName(KEYBOARD_EVENT.keysym.sym) + 5);
                    break;
                case SDL_KEYUP:
                    args[0]["onKeyUp"](SDL_GetKeyName(KEYBOARD_EVENT.keysym.sym) + 5);
                    break;
                case RedrawEvent:
                    args[0]["onRedraw"](Drawer);
                    break;
            }
        }
        stSDL_Release();
    }
}
