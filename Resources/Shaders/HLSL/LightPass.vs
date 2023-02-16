cbuffer CameraData: register(b1){
    matrix<float, 4, 4> view;
    float4 cameraPos;
}

struct VS_OUT{
    float4 position : SV_POSITION;
    float3 cameraPos: CameraPos;
    float2 texCoords: TexCoords;
};

VS_OUT main(float2 position: Position, float2 texCoords: TexCoords){
    VS_OUT output;
    output.position = float4(position, 0.0, 1.0);
    output.cameraPos = cameraPos.xyz;
    output.texCoords = texCoords;
    return output;
}