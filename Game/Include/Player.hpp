//
// Created by Shreejit Murthy on 14/10/2024.
//

#pragma once

#include "Actor.hpp"

class Player : Actor {
public:
    Player(std::string path,
           TextureQuad quad = { 0, 0, 0, 0 },
           const glm::vec2& position = { 0, 0 },
           const glm::vec2& scale = { 1, 1 }
    );

    void update(Keyboard* kb, float deltaTime) override;
    void render(Shader shader) override;

    glm::vec2 position;
private:
    glm::vec2 scale;
    TextureQuad quad;
    float moveSpeed;
    glm::vec4 tint;
    float tintTime;
    float tintUpdateSpeed;
};
