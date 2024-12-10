#[===[

cd build
cmake ..
cmake --build . --target Relic
./Relic

cmake --build . --target Relic && ./Relic

]===]

cmake_minimum_required(VERSION 3.28)
project(Relic)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Vendor/SDL)
add_subdirectory(Vendor/glm)
add_subdirectory(Vendor/freetype)
add_subdirectory(Vendor/tmxlite/tmxlite)

set(IMGUI_DIR "Vendor/imgui")

set(ENGINE_SOURCES
        Engine/Source/Window.cpp
        Engine/Source/Keyboard.cpp
        Engine/Source/Shader.cpp
        Engine/Source/Texture.cpp
        Engine/Source/Camera2D.cpp
        Engine/Source/Font.cpp
        Game/Source/Spritesheet.cpp
        Engine/Source/Shape.cpp
        Engine/Source/System.cpp
        Engine/Source/Renderer.cpp
        Engine/Source/Audio.cpp
)

set(GAME_SOURCES
        Game/main.cpp
        Game/Source/Player.cpp
)

set(DEP_SOURCES
        Vendor/glad/glad.c
        Vendor/log/log.c
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendor
        ${CMAKE_CURRENT_SOURCE_DIR}/Game/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glad
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/tmxlite/tmxlite/include
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backend
)

find_package(OpenGL REQUIRED)

set(RELIC_COMMON_LIBS
    OpenGL::GL
    glm::glm
    SDL3::SDL3
    freetype
    tmxlite
)

add_executable(Relic ${ENGINE_SOURCES} ${GAME_SOURCES} ${DEP_SOURCES})

if(WIN32)
    list(APPEND RELIC_COMMON_LIBS winmm) # WASAPI/DirectSound
elseif(APPLE)
    list(APPEND RELIC_COMMON_LIBS "-framework AudioToolbox")
elseif(UNIX)
    find_library(ALSA_LIB NAMES asound)
    if(ALSA_LIB)
        list(APPEND RELIC_COMMON_LIBS ${ALSA_LIB}) # ALSA for Linux
    else()
        message(FATAL_ERROR "ALSA library not found!")
    endif()
endif()

target_link_libraries(Relic ${RELIC_COMMON_LIBS})

# Define compile-time definitions (for the logger)
target_compile_definitions(Relic PRIVATE LOG_USE_COLOR)
