new_shared_library(stSDL)
TARGET_LINK_LIBRARIES(stSDL SDL2 SDL2_image)

new_copy_only(stSDL.st stSDL.st)
ADD_DEPENDENCIES(stSDL stSDL.st)

