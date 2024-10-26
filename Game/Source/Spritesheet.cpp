//
// Created by Shreejit Murthy on 26/10/2024.
//

#include "Spritesheet.h"

Animation::Animation(std::vector<TextureQuad> frames, float delay) {
    this->frames = frames;
    this->delay = delay;
    currentTime = 0;
    currentIndex = 1;
}

void Animation::update(float dt) {
    currentTime += dt;

    if (currentTime >= delay) {
        currentTime -= delay;
        currentIndex = (currentIndex + 1) % frames.size();
    }
}

Spritesheet::Spritesheet(std::string path, int frameWidth, int frameHeight) {
    texture = std::make_unique<Texture>(path);
    frameDimensions = {frameWidth, frameHeight};
}

std::vector<TextureQuad> Spritesheet::getFramesInRow(int sx, int sy, int fx, int fy) const {
    std::vector<TextureQuad> f;
    for (int y = sy; y <= fy; ++y) {
        for (int x = sx; x <= fx; ++x) {
            float xPos = (x - 1) * frameDimensions.x;
            float yPos = (y - 1) * frameDimensions.y;

            f.push_back({xPos, yPos, frameDimensions.x, frameDimensions.y});
        }
    }
    return f;
}

Animation Spritesheet::newAnimation(const std::array<int, 2>& s, const std::array<int, 2>& f, float delay) {
    auto [sx, sy] = s;
    auto [fx, fy] = f;
    auto frames = getFramesInRow(sy, sx, fy + 1, fx);

    return Animation(frames, delay);
}

void Spritesheet::draw(SpritesheetDrawArgs args) {
    texture->draw((TextureDrawArgs){
        .position = args.position,
        .quad = args.animation.frames.at(args.animation.currentIndex),
        .shader = args.shader,
    });
}
