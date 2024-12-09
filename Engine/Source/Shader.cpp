//
// Created by Shreejit Murthy on 29/9/2024.
//

#include <SDL3/SDL_iostream.h>
#include "Shader.hpp"
#include <glad/glad.h>
#include <log/log.h>
#include <glm/gtc/type_ptr.hpp>

#include "System.hpp"

void Shader::checkCompileErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];
    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            log_error("SHADER::Compilation error of type: %s, %s", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            log_error("SHADER::Program linking error of type: %s, %s", type, infoLog);
        }
    }
}

char* Shader::readFile(const char* filePath) {
    if (filePath != nullptr) {
        // Open the file
        SDL_IOStream* io = SDL_IOFromFile(filePath, "rb");
        if (io == nullptr) {
            log_error("FILE_IO::File unsuccessfully read: %s", filePath);
            return nullptr;
        }

        // Get the length of the file
        Sint64 length = SDL_GetIOSize(io);
        if (length < 0) {
            log_error("FILE_IO::SDL_IOStream file size error");
            SDL_CloseIO(io);
            return nullptr;
        }

        // Allocate memory to read the file content
        char* content = (char*)malloc(length + 1);
        if (content == nullptr) {
            log_error("FILE_IO::File memory allocation failed");
            SDL_CloseIO(io);
            return nullptr;
        }

        // Read the file content
        Sint64 bytesRead = SDL_ReadIO(io, content, length);
        if (bytesRead != length) {
            log_error("FILE_IO::SDL_IOStream file read error");
            free(content);
            SDL_CloseIO(io);
            return nullptr;
        }

        // Null-terminate the content
        content[length] = '\0';

        SDL_CloseIO(io);
        return content;
    } else {
        return nullptr;
    }
}

void Shader::load(const char* vertex_path, const char* fragment_path) {
    std::string vertexPath = System::findPathUpwards(vertex_path);
    std::string fragmentPath = System::findPathUpwards(fragment_path);

    char* vertexCode = readFile(vertexPath.c_str());
    char* fragmentCode = readFile(fragmentPath.c_str());

    // 2. compile Shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const GLchar* const*)&vertexCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const GLchar* const*)&fragmentCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the Shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertexCode);
    free(fragmentCode);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::set_mat4(const char* name, glm::mat4 mat) {
    unsigned int location = glGetUniformLocation(ID, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::set_vec3(const char *name, glm::vec3 vec) {
    glUniform3f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z);
}

void Shader::set_vec4(const char *name, glm::vec4 vec) {
    glUniform4f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setUniformName(const std::string& uniformType, const std::string& name) {
    // This sucks cheeks.
    if (uniformType == "model") {
        uniforms.model = name;
    } else if (uniformType == "tint") {
        uniforms.tint = name;
    } else if (uniformType == "textColour") {
        uniforms.textColour = name;
    } else if (uniformType == "shapePos") {
        uniforms.shapePos = name;
    } else if (uniformType == "shapeScale") {
        uniforms.shapeScale = name;
    } else if (uniformType == "shapeSizePixel") {
        uniforms.shapeSizePixel = name;
    } else if (uniformType == "shapeDrawColour") {
        uniforms.shapeDrawColour = name;
    } else if (uniformType == "shapeType") {
        uniforms.shapeType = name;
    }
}

