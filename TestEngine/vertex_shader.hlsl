struct VS_INPUT
{
    float3 position : POSITION;
    float3 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output;
    output.position = float4(input.position, 1.0f); // Conversion en 4D
    output.color = input.color;
    return output;
}