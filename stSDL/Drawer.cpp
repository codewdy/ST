#include "stSDL.h"
namespace stSDL {
    pObject Drawer;
    pObject ReDraw;
    static std::unique_ptr<SDL_Rect> rect(pObject r) {
        if (r.ref_equal(ToolKit::null))
            return nullptr;
        else
            return std::unique_ptr<SDL_Rect>(new SDL_Rect({ST_TO(r["Left"], Integer), ST_TO(r["Top"], Integer),
                    ST_TO(r["Width"], Integer), ST_TO(r["Height"], Integer)}));
    }
    void InitDrawer() {
        Drawer = new BaseType::State();
        Drawer["DrawSurface"] = ST_FUNC_ARG(==2, {
            //TODO
            SDL_Surface* xx = args[0].To<Surface_t>();
            SDL_BlitSurface(xx, rect(args[0]["Rect"]).get(), gSurface, rect(args[1]).get());
        });
        Drawer["DrawSurfaceScaled"] = ST_FUNC_ARG(==2, {
            //TODO
            SDL_Surface* xx = args[0].To<Surface_t>();
            //SDL_BlitScaled(xx, rect(args[0]["Rect"]).get(), gSurface, rect(args[1]).get());
            SDL_Texture* text = SDL_CreateTextureFromSurface(gRender, xx);
            SDL_RenderCopy(gRender, text, rect(args[0]["Rect"]).get(), rect(args[1]).get());
        });
        ReDraw = ST_FUNC_ARG(==0, {
            SDL_Event e;
            e.type = SDL_WINDOWEVENT;
            e.window.windowID = SDL_GetWindowID(gWindow);
            e.window.event = SDL_WINDOWEVENT_EXPOSED;
            SDL_PushEvent(&e);
        });
    }
}
