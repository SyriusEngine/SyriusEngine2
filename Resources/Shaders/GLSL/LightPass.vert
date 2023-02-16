#version 460

layout(location = 0) in vec2 lPosition;
layout(location = 1) in vec2 lTexCoord;

out Resource{
    vec2 texCoords;
    vec3 cameraPos;
} res;

layout(std140, binding = 1) uniform CameraData {
    mat4 view;
    vec4 cameraPos;
};

void main(){
    res.texCoords = lTexCoord;
    res.cameraPos = cameraPos.xyz;
    gl_Position = vec4(lPosition, 0.0, 1.0);
}