struct VSout{
    float4 position : SV_Position;
    float2 texCoords: TexCoords;
};

VSout main(float2 position: Position, float2 texCoords: TexCoords){
    VSout output;
    output.position = float4(position, 0.0f, 1.0f);
    output.texCoords = texCoords;
    return output;
}