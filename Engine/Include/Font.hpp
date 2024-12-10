//
// Created by Shreejit Murthy on 3/10/2024.
//

#pragma once

#include <glm/glm.hpp>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.hpp"

struct Character {
    unsigned int ID;       // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    unsigned int advance;  // Offset to advance to next glyph
};

class Font {
public:
    Font(const char* path);
    ~Font();
    void print(std::string text, glm::vec2 position, Shader shader, glm::vec4 colour, float scale);
private:
    unsigned int _VAO, _VBO;
    float _s;
    glm::vec4 _colour;
    Character _characterData;
    FT_Library ft;
    std::map<char, Character> characters;
};
