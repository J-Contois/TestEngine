#ifndef MESH_H
#define MESH_H

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

struct Vertex {
    XMFLOAT3 position;
    XMFLOAT3 color;
};

class Mesh {
public:
    Mesh();
    ~Mesh();
    bool Init(ID3D11Device* device);
    void Render(ID3D11DeviceContext* context);
    void Clean();

private:
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    int indexCount;
};

#endif
