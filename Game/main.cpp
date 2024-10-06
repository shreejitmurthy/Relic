#include "Window.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Math.hpp"
#include "Texture.hpp"
#include "Camera2D.hpp"
#include "Actor.hpp"

#include <cmath>
#include <iostream>

const int screenWidth = 800, screenHeight = 600;

class Player : Actor {
public:
    Player(std::string path, TextureQuad quad = { 0, 0, 0, 0 }, const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 })
    {
        _texture = new Texture(path);
        this->position = position;
        this->scale = scale;
        _tintTime = 0.0f;
        _tintUpdateSpeed = 0.05f;
        _tint = {1, 1, 1, 1};
        this->quad = quad;

    }

    void update(Keyboard* kb, float deltaTime) override {
        // update based on keyboard input
        _tintTime += _tintUpdateSpeed;
        _tint.a = (sin(_tintTime) + 1.0f) / 2.0f;

        if (kb->isDown(SDLK_LEFT)) {
            position.x -= 1;
            std::cout << "Container x-pos: " << position.x << std::endl;
        }
    }

    void render(Shader shader) override {
        TextureQuad drawQuad;
        if (quad.w == 0 || quad.h == 0) {
            drawQuad = {
                    0, 0,
                    static_cast<float>(_texture->getWidth()),
                    static_cast<float>(_texture->getHeight())
            };
        } else {
            drawQuad = quad;
        }
        _texture->draw((TextureDrawArgs){
                .position = position,
                .quad = drawQuad,
                .scale = scale,
                .tint = _tint,
                .shader = shader,
        });
    }

    glm::vec2 position;
    glm::vec2 scale;
    TextureQuad quad;
    float moveSpeed;
private:
    Texture* _texture;
    glm::vec4 _tint;
    float _tintTime;
    float _tintUpdateSpeed;
};

int main() {
    Window window((WindowArgs){
        .title = "Window",
        .width = screenWidth,
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

    Player player("../Game/resources/container.png", {0, 0, 256, 256}, position, {1, 1});


    Texture knight("../Game/resources/knight.png");

    Camera2D cam(textureShader, screenWidth, screenHeight);
    cam.setPosition({0, 0});
    cam.setZoom(0.5);

    glm::mat4 fontProjection = glm::ortho(
            0.f, static_cast<float>(screenWidth),
            0.f, static_cast<float>(screenHeight),
            -1.f, 1.f);

    Font font("../Game/resources/Roboto-Regular.ttf");

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

        knight.draw((TextureDrawArgs){
            .position = {200, 300},
            .scale = {3, 3},
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