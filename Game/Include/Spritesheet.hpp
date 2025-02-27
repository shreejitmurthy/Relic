//
// Created by Shreejit Murthy on 26/10/2024.
//
// Effectively a C++ and in-house engine port of https://github.com/shreejitmurthy/LOVE-spritesheets

#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>

#include "Font.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"

class Animation {
public:
    Animation(std::vector<TextureQuad> frames, float delay, bool loop);
    void update(float dt);
    void reset();
    std::vector<TextureQuad> frames;
    float delay;
    float currentTime;
    int currentIndex;
    bool completed;
    bool loop;
    std::unordered_map<int, float> frameDelays;
};

typedef struct {
    Animation animation;
    glm::vec2 position;
    glm::vec4 tint;
    Shader shader;
} SpritesheetDrawArgs;

class Spritesheet {
public:
    Spritesheet(std::string path, int frameWidth, int frameHeight);
    Animation newAnimation(const std::array<int, 2>& s, const std::array<int, 2>& f, float delay, bool loop = true);
    void draw(Renderer& renderer, Animation animation, glm::vec2 position, glm::vec4 tint = {1.f, 1.f, 1.f, 1.f});
private:
    std::vector<TextureQuad> getFramesInRow(int sRow, int sCol, int fRow, int fCol) const;
    std::unique_ptr<Texture> texture;
    glm::vec2 frameDimensions;
};
