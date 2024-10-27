#include "Window.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Math.hpp"
#include "Camera2D.hpp"

#include "Player.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl3.h>
#include <imgui/backends/imgui_impl_opengl3.h>

const int screenWidth = 800, screenHeight = 600;

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
//    im_window_flags |= ImGuiWindowFlags_NoResize;
//    im_window_flags |= ImGuiWindowFlags_NoMove;

    ImGui_ImplSDL3_InitForOpenGL(window.window, window.ctx);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsDark();

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

    Player player(position, scale);

    Camera2D cam(textureShader, screenWidth, screenHeight);
    cam.setPosition({0, 0});
    cam.setZoom(2);

    glm::mat4 fontProjection = glm::ortho(
            0.f, static_cast<float>(screenWidth),
            0.f, static_cast<float>(screenHeight),
            -1.f, 1.f);

    Font font("../Game/Resources/Roboto-Regular.ttf");

    while (window.windowOpen()) {
        if (window.kb->isDown(SDLK_ESCAPE)) {
            window.open = false;
        }

        ImGui_ImplSDL3_ProcessEvent(&window.event);

        player.update(window.kb, window.deltaTime);
        cam.setPosition(player.position);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Debug", nullptr, im_window_flags);

            ImGui::SetWindowPos({5, 5});

            ImGui::Text("Player Animation Index: %d", player.currentAnimation->currentIndex);

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 0.5));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::PopStyleColor();
            ImGui::End();
        }

        ImGui::Render();

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        cam.attach();

        player.render(textureShader);

        cam.detach();

        fontShader.use();
        fontShader.set_mat4("projection", fontProjection);

//        std::string index = "Current Animation Index: " + std::to_string(player.currentAnimation->currentIndex);

        font.print((FontPrintArgs){
            .text = "Sigma Game",
            .position = {10, 10},
            .colour = {1, 1, 1, 0.2},
            .scale = 0.5,
            .shader = fontShader,
        });

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.refresh();
    }

    return 0;
}