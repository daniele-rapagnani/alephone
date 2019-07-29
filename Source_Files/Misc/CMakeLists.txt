
add_library(
        misc STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ActionQueues.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CircularByteBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Console.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DefaultStringSets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/game_errors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PlayerImage_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PlayerName.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/preferences.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/preference_dialogs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/preferences_widgets_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Scenario.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sdl_dialogs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/thread_priority_sdl_posix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sdl_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shared_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vbl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Statistics.cpp
)