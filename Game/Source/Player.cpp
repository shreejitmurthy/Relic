//
// Created by Shreejit Murthy on 14/10/2024.
//

#include "Player.hpp"
#include <string_view>

STATE Next(STATE dir) {
    // Move to the next enum value; wrap around using COUNT
    return static_cast<STATE>((static_cast<int>(dir) + 1) % static_cast<int>(STATE::WRAP));
}

// Helper function to move to the previous value in the enum
STATE Previous(STATE dir) {
    // Move to the previous enum value; wrap around using COUNT
    return static_cast<STATE>((static_cast<int>(dir) - 1 + static_cast<int>(STATE::WRAP)) % static_cast<int>(STATE::WRAP));
}

Player::Player() {
    this->position = glm::vec2(400, 300);
    this->scale = glm::vec2(1, 1);
    tint = {1, 1, 1, 1};

    sheet = std::make_shared<Spritesheet>("../Game/Resources/V1/player_V1.png", 48, 48);
    animations[STATE::IDLE] = std::make_shared<Animation>(sheet->newAnimation({1, 1}, {1, 10}, 0.1));
    animations[STATE::RUN] = std::make_shared<Animation>(sheet->newAnimation({2, 1}, {2, 8}, 0.07));
    animations[STATE::JUMP] = std::make_shared<Animation>(sheet->newAnimation({3, 1}, {3, 3}, 0.15, false));
    animations[STATE::FALL] = std::make_shared<Animation>(sheet->newAnimation({3, 3}, {3, 4}, 0.5));
    animations[STATE::LAND] = std::make_shared<Animation>(sheet->newAnimation({4, 1}, {4, 9}, 0.1));
    state = STATE::IDLE;
    currentAnimation = animations[state];
}

void Player::update(Keyboard *kb, float deltaTime) {
    if (kb->isDown(SDLK_LEFT)) {
        position.x -= 1;
    } else if (kb->isDown(SDLK_RIGHT)) {
        position.x += 1;
    }

    // NOTE: This is just temporary
    if (kb->isPressed(SDLK_RIGHT)) {
        state = Next(state);
    } else if (kb->isPressed(SDLK_LEFT)) {
        state = Previous(state);
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
