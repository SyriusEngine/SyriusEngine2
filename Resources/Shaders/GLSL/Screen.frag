#version 460

layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D screenTexture;

in vec2 vTexCoords;

void main() {
    fragColor = texture(screenTexture, vTexCoords);
}