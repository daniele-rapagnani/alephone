
add_library(
        input STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/mouse_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/joystick_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/touch_sdl.cpp
)