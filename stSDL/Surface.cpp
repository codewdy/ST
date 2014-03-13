#include "stSDL.h"
#include <SDL2/SDL_image.h>

namespace stSDL {
    pObject Surface;
    pObject Rect;
    void InitSurface() {
        Surface = new BaseType::State();
        Surface["__init__"] = ST_FUNC({
            if (args.size() != 2 && args.size() != 3)
                ST_ARG_ERROR;
            std::string fn = args[1]["__str__"]().To<std::string>();
            args[0].SetObj<Surface_t>(IMG_Load(fn.c_str()));
            if (args.size() == 3)
                args[0]["Rect"] = args[2];
            else
                args[0]["Rect"] = ToolKit::null;
            return args[0];
        });
        Rect = new BaseType::State();
        Rect["__init__"] = ST_FUNC_ARG(==5, {
            args[0]["Left"] = args[1];
            args[0]["Top"] = args[2];
            args[0]["Width"] = args[3];
            args[0]["Height"] = args[4];
            return args[0];
        });
    }
}
