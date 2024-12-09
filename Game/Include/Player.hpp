//
// Created by Shreejit Murthy on 14/10/2024.
//

#pragma once

#include "Actor.hpp"
#include "Renderer.hpp"
#include <unordered_map>
#include <memory>

#include "Spritesheet.hpp"

enum class STATE {
    IDLE,
    RUN,
    JUMP,
    FALL,
    LAND,

    WRAP,
};

class Player : Actor {
public:
    Player();
    ~Player() override = default;

    void update(Keyboard* kb, float deltaTime) override;
    void render(Renderer& renderer) override;

    glm::vec2 position;

    std::shared_ptr<Spritesheet> sheet;
    std::unordered_map<STATE, std::shared_ptr<Animation>> animations;
    std::shared_ptr<Animation> currentAnimation;
    STATE state;
private:
    glm::vec2 scale;
    float moveSpeed;
    glm::vec4 tint;
};
