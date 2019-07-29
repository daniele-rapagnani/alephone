
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/CSeries
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Files
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/GameWorld
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Input
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Misc
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Lua
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Expat
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/FFmpeg
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/ModelView
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Network
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/RenderMain
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/RenderOther
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Sound
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/XML
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Network/Metaserver
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/TCPMess
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/LibNAT
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source_Files)