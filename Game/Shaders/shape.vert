#version 410
layout (location = 0) in vec2 posIn;

uniform vec2 posUL;
uniform vec2 scaleWH;
uniform mat4 projection;

out vec2 posFrag;

void main() {
    // Scale and translate the position
    vec2 scaledPos = posIn * scaleWH + posUL;

    // Apply the projection matrix
    gl_Position = projection * vec4(scaledPos, 0.0, 1.0);

    posFrag = posIn;
}
