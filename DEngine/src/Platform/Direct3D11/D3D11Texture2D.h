#pragma once
#include <d3d11_4.h>
#include "DEngine/Graphics/Texture2D.h"
#include "Platform/Direct3D11/Direct3D11Context.h"
namespace DEngine {


	class D3D11Sampler : public Sampler
	{
	private:
		static Direct3D11Context* graphicsContext;
	public:
		static void SetGraphicsContext(Direct3D11Context* gc);
	private:
		ID3D11SamplerState* SamplerState = nullptr;
	public:
		virtual void PSSet(const unsigned int slot) const override;
		D3D11Sampler(ID3D11SamplerState* samplerState);
		virtual ~D3D11Sampler();
	};
	class D3D11Texture2D : public Texture2D
	{
	private:
		static Direct3D11Context* graphicsContext;
	public:
		static void SetGraphicsContext(Direct3D11Context* gc);
	private:
		ID3D11Texture2D* Texture = nullptr;
		ID3D11ShaderResourceView* TextureResourceView = nullptr;
	public:
		virtual void PSSet(const unsigned int slot) const override;
		D3D11Texture2D(ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureResourceView);
		virtual ~D3D11Texture2D();
	};
}