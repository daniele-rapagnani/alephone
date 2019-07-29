
add_library(
        expat STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/xmlparse.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xmlrole.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xmltok.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xmltok_impl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xmltok_ns.c
)