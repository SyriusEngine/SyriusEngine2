#version 460

in Resource{
    vec2 texCoords;
    vec3 position;
    vec3 cameraPos;
    mat3 TBN;
} res;

layout(location = 0) out vec4 fragColor;

void main() {
    fragColor = vec4(0.5f, 0.3f, 0.8f, 1.0f);
}