#version 410
layout (location = 0) in vec2 posIn;

uniform vec2 posUL;
uniform vec2 scaleWH;

out vec2 posFrag;

void main() {
    vec2 scaledPos = posIn * scaleWH + posUL;

    gl_Position = vec4(scaledPos, 0.0, 1.0);

    posFrag = posIn;
}
