//
// Created by Shreejit Murthy on 2/10/2024.
//

#pragma once

#include "Shader.hpp"

class Camera2D {
public:
    Camera2D(Shader desiredShader, int width, int height);
    void setPosition(glm::vec2 p);
    void setZoom(float z);
    glm::mat4 getView();
    glm::mat4 getProjection();
    void attach();
    void detach();
private:
    Shader* _shader;
    float _zoom;
    glm::vec2 _position;
    glm::mat4 _projection;
    glm::mat4 _view;
    int _width, _height;
};
