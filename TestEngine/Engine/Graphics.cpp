#include "Graphics.h"

bool Graphics::Init(HWND hWnd) {
    return InitD3D(hWnd);
}

bool Graphics::InitD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferDesc.Width = 800;
    scd.BufferDesc.Height = 600;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.SampleDesc.Count = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hWnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &scd, &swapChain, &device, nullptr, &context);

    if (FAILED(hr)) return false;

    ID3D11Texture2D* backBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    if (!InitD3D(hWnd)) return false;

    mesh = new Mesh();
    if (!mesh->Init(device)) return false;

    shader = new Shader();
    if (!shader->LoadShader(device, L"shader.hlsl")) return false;

    return true;
}

void Graphics::Render() {
    float clearColor[4] = { 0.2f, 0.2f, 0.4f, 1.0f };
    context->ClearRenderTargetView(renderTargetView, clearColor);

    shader->Use(context);
    mesh->Render(context);

    swapChain->Present(1, 0);
}

void Graphics::Clean() {
    swapChain->Release();
    device->Release();
    context->Release();
    renderTargetView->Release();
}
