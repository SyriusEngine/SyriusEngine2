#version 460

layout(location = 0) in vec2 lPosition;
layout(location = 1) in vec2 lTexCoords;

out vec2 vTexCoords;

void main() {
    vTexCoords = lTexCoords;
    gl_Position = vec4(lPosition, 0.0f, 1.0f);

}