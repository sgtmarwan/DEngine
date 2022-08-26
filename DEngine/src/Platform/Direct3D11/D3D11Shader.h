#pragma once
#include <d3d11_4.h>

#include "DEngine/Graphics/Shader.h"
#include "Direct3D11Context.h"
namespace DEngine
{
	struct D3D11ShaderData : public ShaderData
	{
		ID3D11Buffer** Data;
		virtual ~D3D11ShaderData();
	};
	class D3D11Shader : public Shader
	{
	private:
		static Direct3D11Context* graphicsContext;
	private:
		ID3D11VertexShader* VertexShader = nullptr;
		ID3D11PixelShader* PixelShader = nullptr;
		ID3D11InputLayout* InputLayout = nullptr;
	public:
		D3D11Shader(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout);
		virtual void Bind();
		virtual void SetVSShaderData(ShaderData* data, unsigned int startIndex) override;
		virtual void SetPSShaderData(ShaderData* data, unsigned int startIndex) override;
		virtual ~D3D11Shader();
	};
}

