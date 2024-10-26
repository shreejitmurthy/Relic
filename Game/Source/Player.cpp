//
// Created by Shreejit Murthy on 14/10/2024.
//

#include "Player.hpp"
#include <iostream>

#include <map>
#include <string_view>

Player::Player(const glm::vec2 &position, const glm::vec2 &scale) {
    this->position = position;
    this->scale = scale;
    tint = {1, 1, 1, 1};

    sheet = std::make_shared<Spritesheet>("../Game/Resources/V1/player_V1.png", 48, 48);
    animations[IDLE] = std::make_shared<Animation>(sheet->newAnimation({1, 1}, {1, 9}, 0.1));
    currentAnimation = animations[IDLE];
}

void Player::update(Keyboard *kb, float deltaTime) {
    if (kb->isDown(SDLK_LEFT)) {
        position.x -= 1;
    } else if (kb->isDown(SDLK_RIGHT)) {
        position.x += 1;
    }

    currentAnimation->update(deltaTime);
}

void Player::render(Shader shader) {
    sheet->draw((SpritesheetDrawArgs){
        .animation = *currentAnimation,
        .position = position,
        .tint = tint,
        .shader = shader
    });
}
