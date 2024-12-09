#version 410

in vec2 posFrag;
uniform float sizePixel;
uniform vec4 drawColor;
uniform int shapeType;
out vec4 FragColor;

void fillOval() {
    float distance = 1.0 - sqrt(posFrag.x * posFrag.x + posFrag.y * posFrag.y) + sizePixel / 2.0;
    float alpha = clamp(distance / sizePixel, 0.0, 1.0);
    if (alpha < 0.01f)
            discard;
    FragColor = vec4(drawColor.xyz, drawColor.w * alpha);
}

void fillRectangle() {
    FragColor = drawColor;
}

void outlineRectangle(float borderThickness) {
    bool isBorder = posFrag.x > 1.0 - borderThickness || posFrag.x < -1.0 + borderThickness ||
    posFrag.y > 1.0 - borderThickness || posFrag.y < -1.0 + borderThickness;
    if (isBorder) {
        FragColor = vec4(drawColor.xyz, drawColor.w);
    } else {
        discard;
    }
}


void main() {
    switch (shapeType) {
        case 1: outlineRectangle(sizePixel); break;
        default: fillRectangle(); break;
    }
}