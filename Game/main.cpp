#include "Window.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Math.hpp"
#include "Camera2D.hpp"

#include "Player.hpp"

const int screenWidth = 800, screenHeight = 600;

int main() {
    Window window((WindowArgs){
        .title = "Window",
        .width = screenWidth,
        .height = screenHeight,
    });

    Shader textureShader((ShaderArgs){
        .vertex_path = "../Game/Shaders/texture.vert",
        .fragment_path = "../Game/Shaders/texture.frag",
    });

    Shader fontShader((ShaderArgs){
            .vertex_path = "../Game/Shaders/font.vert",
            .fragment_path = "../Game/Shaders/font.frag",
    });

    glm::vec2 position = glm::vec2(400, 300);
    glm::vec2 scale = glm::vec2(1, 1);

    Player player("../Game/Resources/V1/Character Idle 48x48.png", {0, 0, 256, 256}, position, scale);

    Camera2D cam(textureShader, screenWidth, screenHeight);
    cam.setPosition({0, 0});
    cam.setZoom(1);

    glm::mat4 fontProjection = glm::ortho(
            0.f, static_cast<float>(screenWidth),
            0.f, static_cast<float>(screenHeight),
            -1.f, 1.f);

    Font font("../Game/Resources/Roboto-Regular.ttf");

    while (window.windowOpen()) {
        if (window.kb->isDown(SDLK_ESCAPE)) {
            window.open = false;
        }

        player.update(window.kb, 0.f);
        cam.setPosition(player.position);

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        cam.attach();

        player.render(textureShader);

        cam.detach();

        fontShader.use();
        fontShader.set_mat4("projection", fontProjection);

        font.print((FontPrintArgs){
            .text = "Sigma Game",
            .position = {10, 10},
            .colour = {1, 1, 1, 0.2},
            .scale = 0.5,
            .shader = fontShader,
        });

        window.refresh();
    }

    return 0;
}