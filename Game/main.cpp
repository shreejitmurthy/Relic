#include "Window.hpp"
#include "Shader.hpp"
#include "Math.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

typedef struct {
    float x, y, w, h;
} TextureQuad;

int main() {
    Window window((WindowArgs){
            .title = "Window",
            .width = 800, .height = 600,
    });

    Shader textureShader((ShaderArgs){
            .vertex_path = "../Game/shaders/texture.vert",
            .fragment_path = "../Game/shaders/texture.frag",
    });


    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("../Game/resources/container.png", &width, &height, &nrChannels, 4);
    if (data) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }

    glm::vec2 position = glm::vec2(400, 300);
    glm::vec2 scale = glm::vec2(1, 1);

    TextureQuad quad = {0, 0, 256, 256};

    float u0 = quad.x / width;
    float v0 = quad.y / height;
    float u1 = (quad.x + quad.w) / width;
    float v1 = (quad.y + quad.h) / height;

    float halfWidth  = quad.w / 2.0f;
    float halfHeight = quad.h / 2.0f;

    std::array<float, 32> vertices = {
            /*     positions         tx coords        colors     */
            halfWidth,  halfHeight,   u1, v1,    1.0f, 0.0f, 0.0f,  // top right
            halfWidth,  -halfHeight,  u1, v0,    0.0f, 1.0f, 0.0f,  // bottom right
            -halfWidth, -halfHeight,  u0, v0,    0.0f, 0.0f, 1.0f,  // bottom left
            -halfWidth, halfHeight,   u0, v1,    1.0f, 1.0f, 0.0f   // top left
    };


    std::array<unsigned int, 6> indices = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glm::mat4 projection = glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f);

    while (window.windowOpen()) {
        if (window.kb->isDown(SDLK_ESCAPE)) {
            window.open = false;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.f); // Reset to identity matrix
        model = glm::translate(model, glm::vec3(position, 0.f));

        textureShader.use();

        glm::mat4 transform = projection * model;

        // Update the shader with the correct transformation matrix
        textureShader.set_mat4("transform", transform);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        window.refresh();
    }

    return 0;
}
