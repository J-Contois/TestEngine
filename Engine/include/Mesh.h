#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <vector>

class Mesh
{
public:
    Mesh(ID3D11Device* device);
    void Render(ID3D11DeviceContext* context);

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
};

