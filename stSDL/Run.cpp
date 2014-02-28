#include "stSDL.h"
#include <iostream>
#include <ST/BuiltinType/Integer.h>
#include <ST/BuiltinType/String.h>

namespace stSDL {
    static bool stSDL_Init(int width, int height, std::string title) {
        gWindow = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
        if (gWindow == nullptr)
            return false;
        gSurface = SDL_GetWindowSurface(gWindow);
        return true;
    }
    static void stSDL_Release() {
        SDL_DestroyWindow(gWindow);
    }
    ST_DEF_FUNC(SDL_Run) {
        if (!stSDL_Init(args[0]["width"].To<BuiltinType::Integer::Inner>(), args[0]["height"].To<BuiltinType::Integer::Inner>(), args[0]["title"].To<BuiltinType::String::Inner>())) {
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
                case SDL_WINDOWEVENT:
                    if (event.window.event = SDL_WINDOWEVENT_EXPOSED) {
                        args[0]["onRedraw"](Drawer);
                        SDL_UpdateWindowSurface(gWindow);
                        break;
                    }
            }
        }
        stSDL_Release();
    }
}
