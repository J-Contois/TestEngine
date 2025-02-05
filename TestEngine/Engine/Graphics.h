#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3d11.h>
#include "Mesh.h"
#include "Shader.h"

class Graphics {
public:
    bool Init(HWND hWnd);
    void Render();
    void Clean();

private:
    Mesh* mesh;
    Shader* shader;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    ID3D11RenderTargetView* renderTargetView = nullptr;

    bool InitD3D(HWND hWnd);
};

#endif

