//
// Created by Shreejit Murthy on 28/10/2024.
//

#include "Shape.hpp"

#include <glad/glad.h>

Shape::Shape(ShapeType shapeType) {
    _type = shapeType;

    float vertices[] = {
            // positions
            -1.0f, -1.0f,
            1.0f, -1.0f,
            1.0f,  1.0f,
            -1.0f,  1.0f
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Shape::draw(ShapeDrawArgs args) {

    _width = (float)args.dimensions.x / args.screenWidth;
    _height = (float)args.dimensions.y / args.screenHeight;
    _x = (2.0f * (float)args.position.x / args.screenWidth) - 1.0f;
    _y = 1.0f - (2.0f * (float)args.position.y / args.screenHeight);

    args.shapeShader.use();

    glUniform2f(glGetUniformLocation(args.shapeShader.ID, "posUL"), _x, _y);
    glUniform2f(glGetUniformLocation(args.shapeShader.ID, "scaleWH"), _width, _height);
    glUniform1f(glGetUniformLocation(args.shapeShader.ID, "sizePixel"), args.pixelSize);
    glUniform1i(glGetUniformLocation(args.shapeShader.ID, "shapeType"), static_cast<GLint>(_type));
    args.shapeShader.set_vec4("drawColor", args.tint);

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
