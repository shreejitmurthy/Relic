#version 410
layout (location = 0) in vec2 posIn;

uniform vec2 posUL;
uniform vec2 scaleWH;
out vec2 posFrag;

void main() {
    // Positioning: Adjust posIn based on scale and upper-left position
    vec2 scaledPos = posIn * scaleWH;
    gl_Position = vec4(scaledPos.x + posUL.x, scaledPos.y + posUL.y, 0.0, 1.0);
    posFrag = posIn;
}
