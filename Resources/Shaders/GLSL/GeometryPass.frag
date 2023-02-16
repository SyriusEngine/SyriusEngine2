#version 460

in Resource{
    vec2 texCoords;
    vec3 position;
    vec3 cameraPos;
    mat3 TBN;
} res;

layout (location = 0) out vec3 gPositions;
layout (location = 1) out vec3 gNormals;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec3 gMrao;

layout(binding = 0) uniform sampler2D albedo;
layout(binding = 1) uniform sampler2D normalTex;
layout(binding = 2) uniform sampler2D metallicTex;
layout(binding = 3) uniform sampler2D roughnessTex;
layout(binding = 4) uniform sampler2D aoTex;

void main() {
    vec4 color = texture(albedo, res.texCoords).rgba;
    vec3 normal = normalize(2.0 * texture(normalTex, res.texCoords).rgb - 1.0);
    vec3 N = normalize(res.TBN * normal);

    float metallic = texture(metallicTex, res.texCoords).r;
    float roughness = texture(roughnessTex, res.texCoords).r;
    float ao = texture(aoTex, res.texCoords).r;

    gPositions = res.position;
    gNormals = N;
    gAlbedo = color;
    gMrao = vec3(metallic, roughness, ao);
}