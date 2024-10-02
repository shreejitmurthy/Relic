//
// Created by Shreejit Murthy on 29/9/2024.
//

#pragma once

#include "glm/glm/glm.hpp"
#include <string>

typedef struct {
    std::string vertex_path;
    std::string fragment_path;
} ShaderArgs;

class Shader {
public:
    Shader(ShaderArgs args);
    void use();
    void set_mat4(const char* name, glm::mat4 mat);
    void set_vec4(const char* name, glm::vec4 vec);
    unsigned int _ID;
private:
    void checkCompileErrors(unsigned int shader, const char* type);
    char* readFile(const char* filePath);
};
