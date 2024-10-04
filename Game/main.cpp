#include "Window.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Math.hpp"
#include "Texture.hpp"
#include "Camera2D.hpp"

#include <cmath>

const int screenWidth = 800, screenHeight = 600;

int main() {
    Window window((WindowArgs){
        .title  = "Window",
        .width  = screenWidth,
        .height = screenHeight,
    });

    Shader textureShader((ShaderArgs){
        .vertex_path = "../Game/shaders/texture.vert",
        .fragment_path = "../Game/shaders/texture.frag",
    });

    Shader fontShader((ShaderArgs){
            .vertex_path = "../Game/shaders/font.vert",
            .fragment_path = "../Game/shaders/font.frag",
    });

    glm::vec2 position = glm::vec2(400, 300);
    glm::vec2 scale = glm::vec2(1, 1);

    TextureQuad quad = {0, 0, 256, 256};

    Texture container("../Game/resources/container.png");
    glm::vec4 containerTint = {1, 1, 1, 1};

    Camera2D cam(textureShader, screenWidth, screenHeight);
    cam.setPosition(position);
    cam.setZoom(1);

    glm::mat4 fontProjection = glm::ortho(
            0.f, static_cast<float>(screenWidth),
            0.f, static_cast<float>(screenHeight),
            -1.f, 1.f);

    Font font("../Game/resources/Roboto-Regular.ttf");

    float time = 0.0f;
    const float speed = 0.05f;

    while (window.windowOpen()) {
        if (window.kb->isDown(SDLK_ESCAPE)) {
            window.open = false;
        }

        time += speed;
        containerTint.a = (sin(time) + 1.0f) / 2.0f;

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        cam.attach();

        container.draw((TextureDrawArgs){
            .position = position,
            .quad = quad,
            .sx = 1, .sy = 1,
            .tint = containerTint,
            .shader = textureShader,
        });

        cam.detach();

        fontShader.use();
        fontShader.set_mat4("projection", fontProjection);

        font.print((FontPrintArgs){
            .text = "Hello, World!",
            .position = position,
            .colour = {0, 1, 0},
            .scale = 1,
            .shader = fontShader,
        });

        window.refresh();
    }

    return 0;
}