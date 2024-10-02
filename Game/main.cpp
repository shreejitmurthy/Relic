#include "Window.hpp"
#include "Shader.hpp"
#include "Math.hpp"
#include "Texture.hpp"
#include "Camera2D.hpp"

int main() {
    Window window((WindowArgs){
            .title = "Window",
            .width = 800, .height = 600,
    });

    Shader textureShader((ShaderArgs){
            .vertex_path = "../Game/shaders/texture.vert",
            .fragment_path = "../Game/shaders/texture.frag",
    });

    glm::vec2 position = glm::vec2(400, 300);
    glm::vec2 scale = glm::vec2(1, 1);

    TextureQuad quad = {0, 0, 256, 256};

    Texture container("../Game/resources/container.png");

    Camera2D cam(textureShader, 800, 600);
    cam.setPosition(position);
    cam.setZoom(1);

    glm::mat4 projection = glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f);

    while (window.windowOpen()) {
        if (window.kb->isDown(SDLK_ESCAPE)) {
            window.open = false;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

//        textureShader.use();
//        textureShader.set_mat4("projection", projection);
        cam.attach();

        container.draw((TextureDrawArgs){
            .position = position,
            .quad = quad,
            .sx = 1, .sy = 1,
            .tint = glm::vec4(1, 1, 1, 1),
            .shader = textureShader,
        });

        cam.detach();

        window.refresh();
    }

    return 0;
}
