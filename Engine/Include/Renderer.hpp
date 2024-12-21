//
// Created by Shreejit Murthy on 9/12/2024.
//

#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Camera2D.hpp"
#include "Window.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>
#include <string>

class Renderer {
public:
    void init(Window& window);
    void beginScene(Camera2D &camera);
    void endScene();

    void render(
            Texture& texture, 
            glm::vec2 position,
            TextureQuad quad = {0.f, 0.f, 0.f, 0.f}, 
            glm::vec2 scale = {1.f, 1.f}, 
            float rotation = 0.f,
            glm::vec4 tint = {0.f, 0.f, 0.f, 0.f});

    void render(Font& font, std::string text, glm::vec2 position, glm::vec4 colour = glm::vec4(1.f), float scale = 1.f);

private:
    Shader textureShader;
    Shader fontShader;
    glm::mat4 projection;
    glm::mat4 view;
    int width, height;
};
