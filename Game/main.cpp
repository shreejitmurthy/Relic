#include "Window.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Math.hpp"
#include "Texture.hpp"
#include "Camera2D.hpp"
#include "Actor.hpp"

#include <cmath>
#include <iostream>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl3.h>
#include <imgui/backends/imgui_impl_opengl3.h>

const int screenWidth = 1280, screenHeight = 720;

class Player : Actor {
public:
    Player(std::string path, TextureQuad quad = { 0, 0, 0, 0 }, const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 })
    {
        texture = new Texture(path);
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
//            std::cout << "Container x-pos: " << position.x << std::endl;
        } else if (kb->isDown(SDLK_RIGHT)) {
            position.x += 1;
        }
    }

    void render(Shader shader) override {
        TextureQuad drawQuad;
        if (quad.w == 0 || quad.h == 0) {
            drawQuad = {
                    0, 0,
                    static_cast<float>(texture->getWidth()),
                    static_cast<float>(texture->getHeight())
            };
        } else {
            drawQuad = quad;
        }
        texture->draw((TextureDrawArgs){
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = nullptr;

    ImGuiWindowFlags im_window_flags = 0;
    im_window_flags |= ImGuiWindowFlags_NoResize;
    im_window_flags |= ImGuiWindowFlags_NoMove;

    ImGui_ImplSDL3_InitForOpenGL(window.window, window.ctx);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsDark();

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

        ImGui_ImplSDL3_ProcessEvent(&window.event);

        player.update(window.kb, 0.f);
        cam.setPosition(player.position);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Debug", nullptr, im_window_flags);

            ImGui::SetWindowPos({5, 5});

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        cam.attach();

        player.render(textureShader);

        knight.draw((TextureDrawArgs){
            .position = {200, 300},
            .scale = {5, 5},
            .rotation = 45.f,
            .shader = textureShader,
        });

        cam.detach();

        fontShader.use();
        fontShader.set_mat4("projection", fontProjection);

        font.print((FontPrintArgs){
            .text = "Hello, World!",
            .position = {500, 200},
            .colour = {0, 1, 0},
            .scale = 1,
            .shader = fontShader,
        });

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.refresh();
    }

    return 0;
}