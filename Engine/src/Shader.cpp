#include "../include/Shader.h"
#include <d3dcompiler.h>
#include <stdexcept>

Shader::Shader(ID3D11Device* device)
{
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;

    D3DCompileFromFile(L"vertex_shader.hlsl", nullptr, nullptr, "VS_Main", "vs_5_0", 0, 0, &vsBlob, nullptr);
    D3DCompileFromFile(L"pixel_shader.hlsl", nullptr, nullptr, "PS_Main", "ps_5_0", 0, 0, &psBlob, nullptr);

    device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
    device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    device->CreateInputLayout(layout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), inputLayout.GetAddressOf());
    vsBlob->Release();
    psBlob->Release();
}

void Shader::Bind(ID3D11DeviceContext* context)
{
    context->IASetInputLayout(inputLayout.Get());
    context->VSSetShader(vertexShader.Get(), nullptr, 0);
    context->PSSetShader(pixelShader.Get(), nullptr, 0);
}

