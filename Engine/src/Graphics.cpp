#include "../include/Graphics.h"
#include <d3dcompiler.h>

Graphics::Graphics(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 800;
    sd.BufferDesc.Height = 600;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;

    D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &sd, swapChain.GetAddressOf(),
        device.GetAddressOf(), nullptr, context.GetAddressOf());

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

    // Initialisation du viewport
    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<float>(sd.BufferDesc.Width);
    viewport.Height = static_cast<float>(sd.BufferDesc.Height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);

    mesh = new Mesh(device.Get());
    shader = new Shader(device.Get());
}

void Graphics::Render()
{
    float color[4] = { 0.8f, 0.2f, 0.4f, 1.0f };
    context->ClearRenderTargetView(renderTargetView.Get(), color);

    shader->Bind(context.Get());
    mesh->Render(context.Get());

    swapChain->Present(1, 0);
}

