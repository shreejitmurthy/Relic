cmake_minimum_required(VERSION 3.28)
project(Relic)

set(CMAKE_CXX_STANDARD 17)

include_directories(vendor)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/glm)

set(RELIC_SOURCES
        Game/main.cpp
        Engine/src/Window.cpp
        Engine/src/Keyboard.cpp
        Engine/src/Shader.cpp
        Engine/src/Texture.cpp
        Engine/src/Camera2D.cpp
        vendor/glad/glad.c
        vendor/log/log.c
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/glad
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/glm
)

find_package(OpenGL REQUIRED)

add_executable(Relic ${RELIC_SOURCES})

target_link_libraries(Relic
        OpenGL::GL
        glm::glm
        SDL3::SDL3
)

# Define compile-time definitions (for the logger)
target_compile_definitions(Relic PRIVATE LOG_USE_COLOR)
