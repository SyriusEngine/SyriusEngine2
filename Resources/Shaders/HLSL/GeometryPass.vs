cbuffer ProjectionData: register(b0){
    matrix<float, 4, 4> perspective;
    matrix<float, 4, 4> orthogonal;
}

cbuffer CameraData: register(b1){
    matrix<float, 4, 4> view;
    float4 cameraPos;
}

cbuffer ModelData: register(b2){
    matrix<float, 4, 4> modelMatrix;
    matrix<float, 4, 4> normalMatrix;
}

struct VS_OUT{
    float4 position: SV_Position;
    float3 cameraPos: CameraPos;
    float2 texCoord: TexCoords;
    matrix<float, 3, 3> TBN: TBNMatrix;
};

VS_OUT main(float3 pos: Position, float3 normal: Normal, float3 tangent: Tangent, float2 texCoords: TexCoords){
    float4 worldPos = mul(modelMatrix, float4(pos, 1.0));
    float4 viewPos = mul(view, worldPos);
    float4 projPos = mul(perspective, viewPos);

    matrix<float, 3, 3> truncNormalMatrix = (float3x3)normalMatrix;
    float3 T = normalize(mul(truncNormalMatrix, tangent));
    float3 B = normalize(cross(normal, T));
    float3 N = normalize(mul(truncNormalMatrix, normal));
    matrix<float, 3, 3> TBN = float3x3(T, B, N);

    VS_OUT output;
    output.position = projPos;
    output.cameraPos = cameraPos.xyz;
    output.texCoord = texCoords;
    output.TBN = TBN;
    return output;
}