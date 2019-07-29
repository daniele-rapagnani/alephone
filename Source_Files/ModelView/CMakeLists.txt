
add_library(
        modelview STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Model3D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ModelRenderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dim3_Loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StudioLoader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WavefrontLoader.cpp
)