//
// Created by Shreejit Murthy on 29/9/2024.
//

#include "Window.hpp"
#include <log/log.h>

Window::Window(WindowArgs args) : _width(args.width), _height(args.height), _title(args.title) {
    log_set_quiet(!args.log);
    kb = new Keyboard();
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        log_error("ENGINE::Initialise Error: %s", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    open = true;

    window = SDL_CreateWindow(_title.c_str(), _width, _height, SDL_WINDOW_OPENGL);
    ctx = SDL_GL_CreateContext(window);

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
        log_error("ENGINE::Failed to initialise GLAD");
    }

    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, _width, _height);

    log_info("ENGINE::Created Window and Context");
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_GL_DestroyContext(ctx);
    log_info("ENGINE::Destroyed GFX");
    SDL_Quit();
    log_info("ENGINE::Goodbye!");
}

bool Window::windowOpen() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                open = false;
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                kb->process(event);
                break;

            default:
                break;
        }
    }

    return open;
}

void Window::refresh() {
    SDL_GL_SwapWindow(window);
}
