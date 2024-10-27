cmake_minimum_required(VERSION 3.28)
project(Relic)

set(CMAKE_CXX_STANDARD 17)

include_directories(Vendor)

add_subdirectory(Vendor/SDL)
add_subdirectory(Vendor/glm)
add_subdirectory(Vendor/freetype)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/Game/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Vendor/glad
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Vendor/glm
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backend
)

find_package(OpenGL REQUIRED)

add_executable(Relic ${ENGINE_SOURCES} ${GAME_SOURCES} ${DEP_SOURCES})

target_link_libraries(Relic
        OpenGL::GL
        glm::glm
        SDL3::SDL3
        freetype
)

# Define compile-time definitions (for the logger)
target_compile_definitions(Relic PRIVATE LOG_USE_COLOR)
