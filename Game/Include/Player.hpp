//
// Created by Shreejit Murthy on 14/10/2024.
//

#pragma once

#include "Actor.hpp"
#include <unordered_map>
#include <memory>

#include "Spritesheet.h"

enum PLAYER_STATES {
    IDLE,
    RUN,
};

class Player : Actor {
public:
    Player(const glm::vec2& position = { 0, 0 },
           const glm::vec2& scale = { 1, 1 }
    );
    ~Player() override = default;

    void update(Keyboard* kb, float deltaTime) override;
    void render(Shader textureShader) override;

    glm::vec2 position;

    std::shared_ptr<Spritesheet> sheet;
    std::unordered_map<PLAYER_STATES, std::shared_ptr<Animation>> animations;
    std::shared_ptr<Animation> currentAnimation;
private:
    glm::vec2 scale;
    float moveSpeed;
    glm::vec4 tint;
};
