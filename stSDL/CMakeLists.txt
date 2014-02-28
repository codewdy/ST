new_shared_library(stSDL)
TARGET_LINK_LIBRARIES(stSDL SDL2 SDL2_image)

new_copy_only(stSDL.st stSDL.st)
new_copy_only(1.png 1.png)
new_copy_only(1.bmp 1.bmp)
ADD_DEPENDENCIES(stSDL stSDL.st 1.png 1.bmp)

