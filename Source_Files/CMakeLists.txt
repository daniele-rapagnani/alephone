
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CSeries)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Expat)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Files)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GameWorld)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Input)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/LibNAT)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Lua)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Misc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ModelView)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Network)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/RenderMain)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/RenderOther)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Sound)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TCPMess)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/XML)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/FFmpeg)

add_library(main SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/shell.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shell_misc.cpp
)

target_link_libraries(main -Wl,--whole-archive cseries expat files gameworld input nat a1lua misc network metaserver rendermain renderother sound tcpmess xml ffmpeg -Wl,--no-whole-archive)