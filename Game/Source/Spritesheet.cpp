//
// Created by Shreejit Murthy on 26/10/2024.
//

#include "Spritesheet.hpp"

#include <iostream>

Animation::Animation(std::vector<TextureQuad> frames, float delay, bool loop) {
    this->frames = frames;
    this->delay = delay;
    this->loop = loop;
    reset();
}

/**
 * Update the animation by updating the index based on set delay.
 * @param dt: Difference in time between two frames.
 */
void Animation::update(float dt) {
    if (!loop && currentIndex == frames.size() - 1) {
        completed = true;
        return;
    }

    currentTime += dt;

    if (currentTime >= delay) {
        currentTime -= delay;

        if (loop) {
            currentIndex = (currentIndex + 1) % frames.size();
        } else {
            if (currentIndex < frames.size() - 1) {
                currentIndex++;
            }
        }
    }
}

void Animation::reset() {
    completed = false;
    currentTime = 0;
    currentIndex = 0;
}

/**
 * Create a Spritesheet object.
 * @param path: Image path of the spritesheet.
 * @param frameWidth: Width of each frame in the sheet.
 * @param frameHeight: Height of each frame in the sheet.
 */
Spritesheet::Spritesheet(std::string path, int frameWidth, int frameHeight) {
    texture = std::make_unique<Texture>(path);
    frameDimensions = {frameWidth, frameHeight};
}

std::vector<TextureQuad> Spritesheet::getFramesInRow(int sRow, int sCol, int fRow, int fCol) const {
    std::vector<TextureQuad> f;
    for (int y = sCol; y <= fCol; ++y) {
        for (int x = sRow; x <= fRow; ++x) {
            float xPos = (x - 1) * frameDimensions.x;
            float yPos = (y - 1) * frameDimensions.y;

            f.push_back({xPos, yPos, frameDimensions.x, frameDimensions.y});
        }
    }
    return f;
}

/**
 * Create a new animation.
 * @param s: Coordinates of starting frame.
 * @param f: Coordinates of ending frame.
 * @param delay: Delay between each frame.
 * @param loop: Default true. Whether the animation loops over itself, or stops at the last frame.
 * @return Animation object.
 */
Animation Spritesheet::newAnimation(const std::array<int, 2>& s, const std::array<int, 2>& f, float delay, bool loop) {
    auto [sx, sy] = s;
    auto [fx, fy] = f;
    auto frames = getFramesInRow(sy, sx, fy, fx);
    Animation animation(frames, delay, loop);

    for (int i = 0; i <= (fx - sx + fy - sy); ++i) {
        animation.frameDelays[i] = delay;
    }

    return animation;
}

/**
 * Draw the spritesheet
 * @param args: animation: Animation object to draw from Spritesheet; position: Location of the drawn Animation; tint: Default {1, 1, 1, 1}. Colour of the drawn Animation; shader: Shader to pass uniforms through.
 */
void Spritesheet::draw(Renderer& renderer, Animation animation, glm::vec2 position, glm::vec4 tint) {
    renderer.render(*texture, position, animation.frames.at(animation.currentIndex));
}
