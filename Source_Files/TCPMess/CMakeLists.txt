
add_library(
        tcpmess STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CommunicationsChannel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MessageDispatcher.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MessageHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MessageInflater.cpp
)