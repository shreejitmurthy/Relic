//
// Created by Shreejit Murthy on 2/10/2024.
//

#include "Camera2D.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D(int width, int height) : _width(width), _height(height) {
    _projection = glm::mat4(0.f);
    _view = glm::mat4(0.f);
    _zoom = 1.f;
    _position = glm::vec2(0.f);
}

void Camera2D::setPosition(glm::vec2 p) {
    _position = p;
}

void Camera2D::setZoom(float z) {
    _zoom = z;
}

glm::mat4 Camera2D::getView() {
    glm::vec3 camera_pos = {0.0f, 0.0f, 1.0f};
    glm::vec3 target_pos = {0.0f, 0.0f, 0.0f};
    glm::vec3 up_vector  = {0.0f, 1.0f, 0.0f};
    return glm::lookAt(camera_pos, target_pos, up_vector);
}

glm::mat4 Camera2D::getProjection() {
    float left   = _position[0] - (_width  / 2.0f) / _zoom;
    float right  = _position[0] + (_width  / 2.0f) / _zoom;
    float top    = _position[1] - (_height / 2.0f) / _zoom;
    float bottom = _position[1] + (_height / 2.0f) / _zoom;

    return glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}
