
add_library(
        metaserver STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/metaserver_dialogs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/metaserver_messages.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_metaserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SdlMetaserverClientUi.cpp
)