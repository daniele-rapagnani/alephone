
add_library(
        files STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/AStream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/crc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/android_assets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/find_files_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/game_wad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/import_definitions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Packing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/preprocess_map_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/preprocess_map_shared.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/resource_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SDL_rwops_ostream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/wad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/wad_prefs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/wad_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WadImageCache.cpp
)