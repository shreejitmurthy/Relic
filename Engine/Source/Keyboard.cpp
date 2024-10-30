//
// Created by Shreejit Murthy on 29/9/2024.
//

#include "Keyboard.hpp"
#include <SDL3/SDL_keycode.h>
#include <log/log.h>

Keyboard::Keyboard() {
    _keys.resize(MAX_KEYS, false);
    _keyPressed.resize(MAX_KEYS, false);
    _keyReleased.resize(MAX_KEYS, false);
    log_info("KEYBOARD::Initialised");
}

void Keyboard::process(SDL_Event event) {
    if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
        if (event.key.scancode < SDL_SCANCODE_COUNT) {
            uint32_t scancode = event.key.scancode;

            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (!_keys[scancode]) {   // Only set _keyPressed if it wasn't already down
                    _keyPressed[scancode] = true;  // Trigger single press event
                }
                _keys[scancode] = true;
            } else if (event.type == SDL_EVENT_KEY_UP) {
                _keys[scancode] = false;
                _keyReleased[scancode] = true;
                _keyPressed[scancode] = false; // Reset pressed state on key release
            }
        }
    }
}

bool Keyboard::isDown(uint32_t key) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, 0);
    return (scancode < SDL_SCANCODE_COUNT && _keys.at(scancode));
}

bool Keyboard::isPressed(uint32_t key) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, 0);
    if (scancode < SDL_SCANCODE_COUNT && _keyPressed[scancode]) {
        _keyPressed[scancode] = false;  // Clear press state after detection
        return true;
    }
    return false;
}

bool Keyboard::isReleased(uint32_t key) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, 0);
    return (scancode < SDL_SCANCODE_COUNT && _keyReleased.at(scancode));
}

void Keyboard::reset() {
    std::fill(_keyReleased.begin(), _keyReleased.end(), false);
}

