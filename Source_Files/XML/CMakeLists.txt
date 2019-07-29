
add_library(
        xml STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Plugins.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/QuickSave.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/InfoTree.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/XML_LevelScript.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/XML_MakeRoot.cpp
)