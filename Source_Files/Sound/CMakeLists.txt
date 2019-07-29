
add_library(
        sound STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/BasicIFFDecoder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Decoder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MADDecoder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Mixer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Music.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ReplacementSounds.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SndfileDecoder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SoundFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SoundManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VorbisDecoder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FFmpegDecoder.cpp
)