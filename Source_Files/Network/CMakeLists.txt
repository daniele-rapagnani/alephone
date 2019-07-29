add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Metaserver)

add_library(
        network STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ConnectPool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_capabilities.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_data_formats.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_dialogs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_dialog_widgets_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_games.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_lookup_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_messages.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_microphone_sdl_alsa.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_microphone_shared.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_speex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_speaker_sdl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_speaker_shared.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_star_hub.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_star_spoke.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_udp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RingGameProtocol.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SDL_netx.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SSLP_limited.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StarGameProtocol.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Update.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HTTP.cpp

)