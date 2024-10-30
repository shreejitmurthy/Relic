//
// Created by Shreejit Murthy on 29/9/2024.
//

#pragma once
#include <SDL3/SDL.h>
#include <vector>

#define MAX_KEYS 322

class Keyboard {
public:
    Keyboard();
    void process(SDL_Event event);
    bool isDown(uint32_t key);
    bool isPressed(uint32_t key);  // Check for key press (single event)
    bool isReleased(uint32_t key); // Check for key release (single event)
    void reset();                  // Reset pressed and released states after processing
private:
    std::vector<bool> _keys;
    std::vector<bool> _keyPressed;
    std::vector<bool> _keyReleased;
};
