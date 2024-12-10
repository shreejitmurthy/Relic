#include "Window.hpp"
#include "Shader.hpp"
#include "Font.hpp"
#include "Math.hpp"
#include "Camera2D.hpp"
#include "Shape.hpp"

#include "Player.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl3.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

//#define SOKOL_AUDIO_IMPL
//#include <sokol_audio.h>

const int screenWidth = 800, screenHeight = 600;

int main() {
    /* OpenGL init*/
    Window window((WindowArgs){
        .title = "Window",
        .width = screenWidth,
        .height = screenHeight,
        .log = true
    });

    Renderer renderer;
    renderer.init(window);

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

    Shader fontShader;
    fontShader.load("Engine/Shaders/font.vert", "Engine/Shaders/font.frag");
    fontShader.setUniformName("textColour", "textColor");

    Shader shapeShader;
    shapeShader.load("Engine/Shaders/shape.vert", "Engine/Shaders/shape.frag");

    Shader bgShader;
    bgShader.load("Game/Shaders/gradient.vert", "Game/Shaders/gradient.frag");

    float bgVertices[] = {
            -1.0f,  1.0f,
            -1.0f, -1.0f,
            1.0f, -1.0f,

            -1.0f,  1.0f,
            1.0f, -1.0f,
            1.0f,  1.0f
    };

    // Set up VAO and VBO for the background gradient quad
    unsigned int bgVAO, bgVBO;
    glGenVertexArrays(1, &bgVAO);
    glGenBuffers(1, &bgVBO);
    glBindVertexArray(bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), &bgVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    // tmx::Map map;
    // map.load("../Game/Maps/basic.tmx");
    // const auto& layers = map.getLayers();
    // const auto& tiles = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();

    // printf("Chunks Count=%d\n", (int)tiles.size());
    // for(int i=0; i<tiles.size(); i++) {
    //     printf("tile id=%d\n", (int)tiles[i].ID);
    // }

    /* Game init */

    glm::vec3 topColor(0, 0.45f, 0.92f);
    glm::vec3 bottomColor(0.76f, 0.49f, 0.59f);

    glm::vec2 position = glm::vec2(400, 300);
    glm::vec2 scale = glm::vec2(1, 1);

    Player player;

    Texture knight("Game/Resources/cool_guy.png");

    Camera2D cam(screenWidth, screenHeight);
    cam.setZoom(2);

    glm::mat4 fontProjection = glm::ortho(
            0.f, static_cast<float>(screenWidth),
            0.f, static_cast<float>(screenHeight),
            -1.f, 1.f);

    Font versionFont("Game/Resources/Roboto-Regular.ttf");
    Font font("Game/Resources/DungeonFont.ttf");

    while (window.windowOpen()) {
        ImGui_ImplSDL3_ProcessEvent(&window.event);
        if (window.kb->isDown(SDLK_ESCAPE)) {
            window.open = false;
        }

        player.update(window.kb, window.deltaTime);

        cam.setPosition(player.position);

        /* GUI Layer */

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Debug", nullptr, im_window_flags);

            ImGui::SetWindowPos({5, 5});

            ImGui::Text("Player Animation Index: %d", player.currentAnimation->currentIndex);
            ImGui::Text("Player Animation Completed: %s", (player.currentAnimation->completed == 1) ? "true" : "false");
            ImGui::Text("Player Position: (%d, %d)", (int)player.position.x, (int)player.position.y);

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 0.4));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::PopStyleColor();
            ImGui::End();
        }

        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT);
        bgShader.use();
        bgShader.set_vec3("topColor", topColor);
        bgShader.set_vec3("bottomColor", bottomColor);

        glBindVertexArray(bgVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        /* World Layer */

        renderer.beginScene(cam);

        renderer.renderTexture(knight, {450, 250});
        player.render(renderer);

        renderer.endScene();
        
        /* Surface Layer */

        renderer.renderFont(versionFont, "Sigma Game", {10, 10}, {1, 1, 1, 0.2}, 0.5);
        
        renderer.renderFont(font, "cool font", {300, 300});

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.refresh();
    }

    return 0;
}
