//
// Created by Shreejit Murthy on 29/9/2024.
//

#include "Keyboard.hpp"
#include <SDL3/SDL_keycode.h>
#include <log/log.h>

Keyboard::Keyboard() {
    for (int i = 0; i < MAX_KEYS; i++) {
        _keys.push_back(false);
    }
    log_info("KEYBOARD::Initialised");
}

void Keyboard::process(SDL_Event event) {
    if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
        if (event.key.scancode < SDL_SCANCODE_COUNT) {
            _keys.at(event.key.scancode) = (event.type == SDL_EVENT_KEY_DOWN);
        }
    }
}

bool Keyboard::isDown(uint32_t key) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, 0);
    return (scancode < SDL_SCANCODE_COUNT && _keys.at(scancode));
}
