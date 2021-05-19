
add_library(
        gameworld STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/devices.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dynamic_limits.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/effects.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/flood_map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/items.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lightsource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/map_constructors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/marathon2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/media.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/monsters.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pathfinding.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/physics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/placement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/platforms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/projectiles.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interpolated_world.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scenery.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/weapons.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/world.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ephemera.cpp
)