struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

float4 PS_Main(PS_INPUT input) : SV_Target
{
    return float4(input.color, 1.0f); // Affichage de la couleur du sommet
}