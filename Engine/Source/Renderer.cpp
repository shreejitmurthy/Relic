//
// Created by Shreejit Murthy on 9/12/2024.
//

#include "Renderer.hpp"
#include <glm/glm.hpp>

#include <log/log.h>

#include <functional>

/*
 * Renderer Goal:
 * Pack images into one file using Python script. 
 * MAYBE: The renderer knows the position and dimensions of each image, and is the one to pack the images.
 * Then submit an object to the renderer, where an image ID and TextureQuad are passed in.
 * The renderer will then render the imageID at a specified position.
 */

// TODO: Implement texture packing

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

void Renderer::render(texture_render_desc desc) {
    desc.quad = desc.quad.w ? desc.quad : TextureQuad{
        0, 0, 
        static_cast<float>(desc.texture.getWidth()), 
        static_cast<float>(desc.texture.getHeight())
    };
    desc.scale = (desc.scale.x || desc.scale.y) ? desc.scale : glm::vec2{1.f, 1.f};
    desc.rotation = desc.rotation ? desc.rotation : 0.f;
    desc.tint = is_zero_colour(desc.tint) ? glm::vec4{1.f, 1.f, 1.f, 1.f} : desc.tint;
    render(desc.texture, desc.position, desc.quad, desc.scale, desc.rotation, desc.tint);
}

void Renderer::render(Font& font, std::string text, glm::vec2 position, glm::vec4 colour, float scale) {
    font.print(text, position, fontShader, colour, scale);
}

void Renderer::render(font_render_desc desc) {
    desc.colour = is_zero_colour(desc.colour) ? glm::vec4{1.f, 1.f, 1.f, 1.f} : desc.colour;
    desc.scale = desc.scale ? desc.scale : 1.f;
    render(desc.font, desc.text, desc.position, desc.colour, desc.scale);
}
