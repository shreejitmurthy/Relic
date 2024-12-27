//
// Created by Shreejit Murthy on 29/9/2024.
//

#pragma once

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include "Keyboard.hpp"
#include <string>

typedef struct {
    std::string title;
    int width, height;
    bool log;
} window_init_desc;

class Window {
public:
    Window(window_init_desc args);
    ~Window();
    bool windowOpen();
    void refresh();

    SDL_Window* window;
    SDL_GLContext ctx;
    Keyboard* kb;
    bool open;
    SDL_Event event;
    int width, height;

    float deltaTime;
private:
    Uint32 _previousTime;
    Uint32 _currentTime;
    std::string _title;
};
