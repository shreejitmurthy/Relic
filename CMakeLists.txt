cmake_minimum_required(VERSION 3.28)
project(Relic)

set(CMAKE_CXX_STANDARD 17)

include_directories(vendor)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/freetype)

set(IMGUI_DIR "vendor/imgui")

set(ENGINE_SOURCES
        Engine/src/Window.cpp
        Engine/src/Keyboard.cpp
        Engine/src/Shader.cpp
        Engine/src/Texture.cpp
        Engine/src/Camera2D.cpp
        Engine/src/Font.cpp
)

set(GAME_SOURCES
        Game/main.cpp
)

set(DEP_SOURCES
        vendor/glad/glad.c
        vendor/log/log.c
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/glad
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/glm
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
