#include "Mesh.h"

Mesh::Mesh() : vertexBuffer(nullptr), indexBuffer(nullptr), indexCount(0) {}

Mesh::~Mesh() {
    Clean();
}

bool Mesh::Init(ID3D11Device* device) {
    // Définition des sommets
    Vertex vertices[] = {
        { XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) }, // Rouge
        { XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) }, // Vert
        { XMFLOAT3(0.0f,  0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }  // Bleu
    };

    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem = vertices;

    HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
    if (FAILED(hr)) return false;

    // Indices pour former un triangle
    unsigned int indices[] = { 0, 1, 2 };
    indexCount = 3;

    D3D11_BUFFER_DESC indexBufferDesc = {};
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(indices);
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem = indices;

    hr = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
    if (FAILED(hr)) return false;

    return true;
}

void Mesh::Render(ID3D11DeviceContext* context) {
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    context->DrawIndexed(indexCount, 0, 0);
}

void Mesh::Clean() {
    if (vertexBuffer) vertexBuffer->Release();
    if (indexBuffer) indexBuffer->Release();
}
