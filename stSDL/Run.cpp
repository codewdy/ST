#include "stSDL.h"
#include <iostream>

namespace stSDL {
    static bool stSDL_Init(int width, int height) {
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
        if (gWindow == nullptr)
            return false;
        gSurface = SDL_GetWindowSurface(gWindow);
        return true;
    }
    static void stSDL_Release() {
        SDL_DestroyWindow(gWindow);
    }
    ST_DEF_FUNC(SDL_Run) {
        if (!stSDL_Init(640, 480)) {
            std::cout << "error" << std::endl;
            //TODO:Exception
        }
        SDL_Event event;
        bool quit = false;
        while (!quit) {
            SDL_WaitEvent(&event);
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        args[0]["onLeftClick"](event.button.x, event.button.y);
                        break;
                    } else if (event.button.button == SDL_BUTTON_RIGHT) {
                        args[0]["onRightClick"](event.button.x, event.button.y);
                        break;
                    }
                    break;
                case SDL_KEYDOWN:
                    args[0]["onKeyDown"](SDL_GetKeyName(event.key.keysym.sym));
                    break;
                case SDL_KEYUP:
                    args[0]["onKeyUp"](SDL_GetKeyName(event.key.keysym.sym));
                    break;
                case SDL_QUIT:
                    quit = args[0]["onQuit"]().To<bool>();
                    break;
                default:
                    if (event.type == RedrawEvent) {
                        args[0]["onRedraw"](Drawer);
                        break;
                    }
            }
        }
        stSDL_Release();
    }
}
