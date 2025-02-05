#include "Shader.h"

bool Shader::LoadShader(ID3D11Device* device, const wchar_t* filename) {
    ID3DBlob* vsBlob;
    ID3DBlob* psBlob;

    D3DCompileFromFile(filename, nullptr, nullptr, "VS_Main", "vs_5_0", 0, 0, &vsBlob, nullptr);
    device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);

    D3DCompileFromFile(filename, nullptr, nullptr, "PS_Main", "ps_5_0", 0, 0, &psBlob, nullptr);
    device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);

    vsBlob->Release();
    psBlob->Release();

    return true;
}

void Shader::Use(ID3D11DeviceContext* context) {
    context->VSSetShader(vertexShader, nullptr, 0);
    context->PSSetShader(pixelShader, nullptr, 0);
}
