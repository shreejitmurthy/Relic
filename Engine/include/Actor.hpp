//
// Created by Shreejit Murthy on 4/10/2024.
//

#pragma once
#include "Shader.hpp"
#include "Keyboard.hpp"

class Actor {
public:
    Actor() {}
    virtual ~Actor() {}

    virtual void update(Keyboard* kb, float deltaTime) = 0;

    // Render method, also meant to be overridden
    virtual void render(Shader shader) = 0;
};
