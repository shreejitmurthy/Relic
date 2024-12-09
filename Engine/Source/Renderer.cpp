//
// Created by Shreejit Murthy on 9/12/2024.
//

#include "Renderer.hpp"
#include <glm/glm.hpp>

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::init(Window& window) {
    textureShader.load("Engine/Shaders/texture.vert", "Engine/Shaders/texture.frag");
    fontShader.load("Engine/Shaders/font.vert", "Engine/Shaders/font.frag");
    width = window.width;
    height = window.height;

}

void Renderer::beginScene(Camera2D& camera) {
    projection = camera.getProjection();
    view = camera.getView();

    textureShader.use();
    textureShader.set_mat4("view", camera.getView());
    textureShader.set_mat4("projection", camera.getProjection());

    fontShader.use();
    fontShader.set_mat4("projection", camera.getProjection());
}

void Renderer::endScene() {
    textureShader.set_mat4("view", glm::mat4(1.f));
    textureShader.set_mat4("projection", glm::ortho(0.f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.f, 1.f));
    fontShader.set_mat4("projection", glm::ortho( 0.f, static_cast<float>(width), 0.f, static_cast<float>(height), -1.f, 1.f));
}

void Renderer::renderTexture(Texture& texture, glm::vec2 position, TextureQuad quad, glm::vec2 scale, float rotation, glm::vec4 tint) {
    texture.draw(position, textureShader, quad, scale, rotation, tint);
}

void Renderer::renderFont(Font& font, FontPrintArgs& args) {

}
