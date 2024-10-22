//
// Created by Shreejit Murthy on 14/10/2024.
//

#include "../Include/Player.hpp"

Player::Player(std::string path, TextureQuad quad, const glm::vec2 &position, const glm::vec2 &scale) {
    texture = new Texture(path);
    this->position = position;
    this->scale = scale;
    tintTime = 0.0f;
    tintUpdateSpeed = 0.05f;
    tint = {1, 1, 1, 1};
    this->quad = quad;
}

void Player::update(Keyboard *kb, float deltaTime) {
    // update based on keyboard input
    tintTime += tintUpdateSpeed;
    tint.a = (sin(tintTime) + 1.0f) / 2.0f;

    if (kb->isDown(SDLK_LEFT)) {
        position.x -= 1;
//            std::cout << "Container x-pos: " << position.x << std::endl;
    } else if (kb->isDown(SDLK_RIGHT)) {
        position.x += 1;
    }
}

void Player::render(Shader shader) {
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
//                .quad = drawQuad,
            .scale = scale,
            .tint = tint,
            .shader = shader,
    });
}
