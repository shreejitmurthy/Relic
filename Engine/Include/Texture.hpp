//
// Created by Shreejit Murthy on 2/10/2024.
//

#pragma once

#include <glad/glad.h>
#include <string>
#include <array>
#include <glm/glm.hpp>
#include "Shader.hpp"

typedef struct {
    float x, y, w, h;
} TextureQuad;

bool is_zero_colour(glm::vec4 colour);

class Texture {
public:
    Texture(const std::string& path);
    void draw(glm::vec2 position, Shader shader, TextureQuad quad, glm::vec2 scale, float rotation,glm::vec4 tint);

    ~Texture();
    int getWidth();
    int getHeight();
    glm::mat4 model;
    glm::vec4 tint;
private:
    void _applyQuad(TextureQuad quad);
    void _genBuffers();
    void _updateVBO();
    GLuint _ID;
    GLuint _VAO, _VBO, _EBO;
    int _width, _height, _nrChannels;
    TextureQuad _quad;
    std::array<float, 32> _vertices;
};
