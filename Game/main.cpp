#include "Window.hpp"
#include "Shader.hpp"
#include "Font.hpp"
#include "Math.hpp"
#include "Camera2D.hpp"
#include "Shape.hpp"

#include "Player.hpp"

#include <iostream>

const int screenWidth = 800, screenHeight = 600;

static Renderer r;

int main() {
    /* OpenGL init */
    Window window((WindowArgs){
        .title = "Window",
        .width = screenWidth,
        .height = screenHeight,
        .log = true
    });

    r.init(window);

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

    /* Game init */

    glm::vec3 topColor(0, 0.45f, 0.92f);
    glm::vec3 bottomColor(0.76f, 0.49f, 0.59f);

    Player player;

    Texture knight("Game/Resources/cool_guy.png");

    Camera2D cam(screenWidth, screenHeight);
    cam.setZoom(2);

    glm::mat4 fontProjection = glm::ortho(
            0.f, static_cast<float>(screenWidth),
            0.f, static_cast<float>(screenHeight),
            -1.f, 1.f);

    Font versionFont("Game/Resources/Roboto-Regular.ttf");

    Font font("Game/Resources/alagard.ttf");

    while (window.windowOpen()) {
        if (window.kb->isDown(SDLK_ESCAPE)) {
            window.open = false;
        }

        player.update(window.kb, window.deltaTime);

        cam.setPosition(player.position);

        glClear(GL_COLOR_BUFFER_BIT);

        bgShader.use();
        bgShader.set_vec3("topColor", topColor);
        bgShader.set_vec3("bottomColor", bottomColor);

        glBindVertexArray(bgVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        /* World Layer */

        r.beginScene(cam);
        
        r.render(knight, {450, 250});
        player.render(r);

        r.endScene();
        
        /* Surface Layer */

        // r.renderFont(versionFont, "Sigma Game", {10, 10}, {1, 1, 1, 0.2}, 0.5);
        r.render(versionFont, "Sigma Game", {10, 10}, {1, 1, 1, 0.2}, 0.5);
        r.render(font, "sugondeez", {425, 300}, glm::vec4(1.f), 0.75f);

        window.refresh();
    }

    return 0;
}
