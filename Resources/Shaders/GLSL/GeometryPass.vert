#version 460

layout(location = 0) in vec3 lPosition;
layout(location = 1) in vec3 lNormal;
layout(location = 2) in vec3 lTangent;
layout(location = 3) in vec2 lTexCoords;

out Resource{
    vec2 texCoords;
    vec3 position;
    vec3 cameraPos;
    mat3 TBN;
} res;

layout(std140, binding = 0) uniform ProjectionData {
    mat4 perspective;
    mat4 orthogonal;
};

layout(std140, binding = 1) uniform CameraData {
    mat4 view;
    vec4 cameraPos;
};

layout(std140, binding = 2) uniform ModelData {
    mat4 modelMatrix;
    mat4 normalMatrix;
};

void main(){
    mat3 truncNormalMatrix = mat3(normalMatrix);
    vec3 fragPos = vec3(modelMatrix * vec4(lPosition, 1.0));

    vec3 N = normalize(truncNormalMatrix * lNormal);
    vec3 T = normalize(truncNormalMatrix * lTangent);
    vec3 B = normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    res.texCoords = lTexCoords;
    res.cameraPos = cameraPos.xyz;
    res.position = fragPos;
    res.TBN = TBN;
    gl_Position = vec4(fragPos, 1.0);
}