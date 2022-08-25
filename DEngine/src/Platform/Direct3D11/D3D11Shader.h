#pragma once
#include <d3d11_4.h>

#include "DEngine/Graphics/Shader.h"
namespace DEngine
{
	struct D3D11Shader : public Shader
	{
	private:
		ID3D11VertexShader* VertexShader = nullptr;
		ID3D11PixelShader* PixelShader = nullptr;
		ID3D11InputLayout* InputLayout = nullptr;
	public:
		D3D11Shader(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout);
		virtual ~D3D11Shader();
	};
}

