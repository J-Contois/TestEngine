#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "Mesh.h"
#include "Shader.h"

class Graphics
{
public:
    Graphics(HWND hWnd);
    void Render();

private:
    Microsoft::WRL::ComPtr<ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    Mesh* mesh;
    Shader* shader;
};
