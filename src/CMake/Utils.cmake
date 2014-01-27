MACRO (new_excutable project)
    AUX_SOURCE_DIRECTORY(. SRC_LIST)
    ADD_EXECUTABLE(${project} ${SRC_LIST})
ENDMACRO ()

MACRO (new_static_library project)
    AUX_SOURCE_DIRECTORY(. SRC_LIST)
    ADD_LIBRARY(${project} STATIC ${SRC_LIST})
ENDMACRO ()

MACRO (new_shared_library project)
    AUX_SOURCE_DIRECTORY(. SRC_LIST)
    ADD_LIBRARY(${project} SHARED ${SRC_LIST})
ENDMACRO ()
