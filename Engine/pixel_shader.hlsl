struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
    return input.color;
}