//
// Created by Shreejit Murthy on 29/9/2024.
//

#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>


// Settable names for the shader uniforms used by Texture, Font and Shape
typedef struct {
    std::string model;
    std::string tint;
    std::string textColour;
    std::string shapePos;
    std::string shapeScale;
    std::string shapeSizePixel;
    std::string shapeDrawColour;
    std::string shapeType;
} ShaderUniforms;

typedef struct {
    std::string vertex_path;
    std::string fragment_path;
} ShaderArgs;

class Shader {
public:
    Shader(ShaderArgs args);
    void use();
    void set_mat4(const char* name, glm::mat4 mat);
    void set_vec3(const char* name, glm::vec3 vec);
    void set_vec4(const char* name, glm::vec4 vec);
    void setUniformName(const std::string& uniformType, const std::string& name);
    unsigned int ID;
    ShaderUniforms uniforms;
private:
    void checkCompileErrors(unsigned int shader, const char* type);
    char* readFile(const char* filePath);
};
