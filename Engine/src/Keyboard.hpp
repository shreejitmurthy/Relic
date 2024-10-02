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
private:
    std::vector<bool> _keys;
};
