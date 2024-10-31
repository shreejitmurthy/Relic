#version 410 core

out vec4 FragColor;

in vec2 TexCoords;

uniform vec3 topColor;
uniform vec3 bottomColor;

void main()  {
    vec3 gradientColor = mix(bottomColor, topColor, TexCoords.y);
    FragColor = vec4(gradientColor, 1.0);
}