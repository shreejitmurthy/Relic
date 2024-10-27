//
// Created by Shreejit Murthy on 28/10/2024.
//

#pragma once

#include <glm/glm.hpp>
#include "Shader.hpp"

enum class ShapeType {
    FillRectangle,
    OutlineRectangle
};

typedef struct {
    glm::vec2 position;
    glm::vec2 dimensions;
    glm::vec4 tint;
    float pixelSize;
    int screenWidth, screenHeight;
    Shader shapeShader;
} ShapeDrawArgs;

class Shape {
public:
    Shape(ShapeType shapeType);
    void draw(ShapeDrawArgs args);
private:
    unsigned int _VAO, _VBO, _EBO;
    float _x, _y;
    float _width, _height;
    ShapeType _type;
};
