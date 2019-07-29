
add_library(
        nat STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/error.c
        ${CMAKE_CURRENT_SOURCE_DIR}/http.c
        ${CMAKE_CURRENT_SOURCE_DIR}/libnat.c
        ${CMAKE_CURRENT_SOURCE_DIR}/os_common.c
        ${CMAKE_CURRENT_SOURCE_DIR}/os_unix.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ssdp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/upnp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/utility.c
)