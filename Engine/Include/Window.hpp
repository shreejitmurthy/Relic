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
} WindowArgs;

class Window {
public:
    Window(WindowArgs args);
    ~Window();
    bool windowOpen();
    void refresh();

    SDL_Window* window;
    SDL_GLContext ctx;
    Keyboard* kb;
    bool open;
    SDL_Event event;

    float deltaTime;
private:
    Uint32 _previousTime;
    Uint32 _currentTime;
    int _width, _height;
    std::string _title;
};
