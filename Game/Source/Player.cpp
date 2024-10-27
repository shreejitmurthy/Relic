//
// Created by Shreejit Murthy on 14/10/2024.
//

#include "Player.hpp"
#include <string_view>

Player::Player() {
    this->position = glm::vec2(400, 300);
    this->scale = glm::vec2(1, 1);
    tint = {1, 1, 1, 1};

    sheet = std::make_shared<Spritesheet>("../Game/Resources/V1/player_V1.png", 48, 48);
    animations[IDLE] = std::make_shared<Animation>(sheet->newAnimation({1, 1}, {1, 10}, 0.1));
    animations[RUN] = std::make_shared<Animation>(sheet->newAnimation({2, 1}, {2, 8}, 0.07));
    state = IDLE;
    currentAnimation = animations[state];
}

void Player::update(Keyboard *kb, float deltaTime) {
    if (kb->isDown(SDLK_LEFT)) {
        position.x -= 1;
    } else if (kb->isDown(SDLK_RIGHT)) {
        position.x += 1;
    }

    if (kb->isDown(SDLK_R)) {
        state = RUN;
    } else if (kb->isDown(SDLK_I)) {
        state = IDLE;
    }

    currentAnimation = animations[state];
    currentAnimation->update(deltaTime);
}

void Player::render(Shader textureShader) {
    sheet->draw((SpritesheetDrawArgs){
        .animation = *currentAnimation,
        .position = position,
        .tint = tint,
        .shader = textureShader
    });
}
