//
// Created by Shreejit Murthy on 9/12/2024.
//

#include "Renderer.hpp"
#include <glm/glm.hpp>

#include <log/log.h>

/*
 * Renderer Goal:
 * - Automatic texture packing for optimisation, this must be done in renderer
 *   and not in the Texture class. We ask to load a variadic amount of textures, then pack it.
 *   Use stb_rect_pack or create our own texture packer that can be ran and checked if already exists
 *   at initialisation.
 *   Then ensure that the renderer knows the locations of each texture, as each texture has it's own
 *   vertices. So the texture packed atlas will have its own vertices to subdivide the textures, then
 *   each texture will have it's own vertices for quads.
*/

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
    
    fontShader.use();
    fontShader.set_mat4("projection", glm::ortho(0.f, static_cast<float>(width), 0.f, static_cast<float>(height), -1.f, 1.f));
}

template<typename First, typename ... T>
bool is_in(First &&first, T && ... t) {
    return ((first == t) || ...);
}

void Renderer::render(Texture& texture, glm::vec2 position, TextureQuad quad, glm::vec2 scale, float rotation, glm::vec4 tint) {
    texture.draw(position, textureShader, quad, scale, rotation, tint);
}

void Renderer::render(Font& font, std::string text, glm::vec2 position, glm::vec4 colour, float scale) {
    font.print(text, position, fontShader, colour, scale);
}
