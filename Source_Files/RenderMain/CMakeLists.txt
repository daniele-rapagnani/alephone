
add_library(
        rendermain STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/AnimatedTextures.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Crosshairs_SDL.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ImageLoader_Shared.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ImageLoader_SDL.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_Faders.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_Model_Def.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_Render.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_Setup.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_Subst_Texture_Def.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_Textures.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/render.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderPlaceObjs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderRasterize.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderSortPoly.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderVisTree.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scottish_textures.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shapes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SW_Texture_Extras.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/textures.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_Shader.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/OGL_FBO.cpp
)