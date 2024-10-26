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
#include "Texture.hpp"
#include "Shader.hpp"

class Animation {
public:
    Animation(std::vector<TextureQuad> frames, float delay);
    void update(float dt);
    std::vector<TextureQuad> frames;
    float delay;
    float currentTime;
    int currentIndex;
};

typedef struct {
    Animation animation;
    glm::vec2 position;
    glm::vec4 tint;
    Shader shader;
    // Still need to implement this debugging, see Lua version for how it's done with LÖVE.
    bool debug;
} SpritesheetDrawArgs;

class Spritesheet {
public:
    Spritesheet(std::string path, int frameWidth, int frameHeight);
    Animation newAnimation(const std::array<int, 2>& s, const std::array<int, 2>& f, float delay);
    void draw(SpritesheetDrawArgs args);
private:
    std::vector<TextureQuad> getFramesInRow(int sx, int sy, int fx, int fy) const;
    std::unique_ptr<Texture> texture;
    glm::vec2 frameDimensions;
};
