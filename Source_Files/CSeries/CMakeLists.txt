
add_library(
        cseries STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/byte_swapping.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BStream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/csalerts_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cscluts_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/csdialogs_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/csmisc_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cspaths_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/csstrings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FilmProfile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mytm_sdl.cpp
)