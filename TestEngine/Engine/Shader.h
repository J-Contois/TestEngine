#ifndef SHADER_H
#define SHADER_H

#include <d3d11.h>
#include <d3dcompiler.h>

class Shader {
public:
    bool LoadShader(ID3D11Device* device, const wchar_t* filename);
    void Use(ID3D11DeviceContext* context);

private:
    ID3D11VertexShader* vertexShader = nullptr;
    ID3D11PixelShader* pixelShader = nullptr;
};

#endif
