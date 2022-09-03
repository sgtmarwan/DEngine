#pragma once
#include <d3d11_4.h>

#include "DEngine/Graphics/Shader.h"
#include "Platform/Direct3D11/Direct3D11Context.h"
namespace DEngine
{
	class D3D11ShaderData : public ShaderData
	{
	private:
		static Direct3D11Context* graphicsContext;
	public:
		static void SetGraphicsContext(Direct3D11Context* gc);
	private:
		ID3D11Buffer* Data = nullptr;
	public:
		virtual void VSSet(const unsigned int slot) const override;
		virtual void PSSet(const unsigned int slot) const override;
		D3D11ShaderData(ID3D11Buffer* data);
		virtual ~D3D11ShaderData();
	};
	class D3D11Shader : public Shader
	{
	private:
		static Direct3D11Context* graphicsContext;
	public:
		static void SetGraphicsContext(Direct3D11Context* gc);
	private:
		ID3D11VertexShader* VertexShader = nullptr;
		ID3D11PixelShader* PixelShader = nullptr;
		ID3D11InputLayout* InputLayout = nullptr;
	public:
		virtual void Bind() const override;
		D3D11Shader(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout);
		virtual ~D3D11Shader();
	};
}

