//
// Created by Shreejit Murthy on 9/12/2024.
//

#include "Renderer.hpp"

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::init() {
    textureShader.load("Engine/Shaders/texture.vert", "Engine/Shaders/texture.frag");
    fontShader.load("Engine/Shaders/font.vert", "Engine/Shaders/font.frag");
}

void Renderer::beginScene(Camera2D &camera) {
    projection = camera.getProjection();
    view = camera.getView();

    textureShader.use();
    textureShader.set_mat4("view", camera.getView());
    textureShader.set_mat4("projection", camera.getProjection());
}

void Renderer::renderTexture(Texture& texture, glm::vec2 position, TextureQuad quad, glm::vec2 scale, float rotation, glm::vec4 tint) {
    texture.draw(position, textureShader, quad, scale, rotation, tint);
}

void Renderer::renderFont(Font& font, FontPrintArgs& args) {

}
