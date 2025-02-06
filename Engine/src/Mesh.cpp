#include "../include/Mesh.h"

struct Vertex
{
    float x, y, z;
    float r, g, b, a;
};

Mesh::Mesh(ID3D11Device* device)
{
    Vertex vertices[] =
    {
        {  0.0f,  0.5f, 0.0f, 1, 0, 0, 1 },
        {  0.5f, -0.5f, 0.0f, 0, 1, 0, 1 },
        { -0.5f, -0.5f, 0.0f, 0, 0, 1, 1 }
    };

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(vertices);
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    device->CreateBuffer(&bufferDesc, &initData, vertexBuffer.GetAddressOf());
}

void Mesh::Render(ID3D11DeviceContext* context)
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    context->Draw(3, 0);
}
