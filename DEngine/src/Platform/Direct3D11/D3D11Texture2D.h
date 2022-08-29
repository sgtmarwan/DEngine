#pragma once
#include <d3d11_4.h>
#include "DEngine/Graphics/Texture2D.h"
namespace DEngine {
	class D3D11Sampler : public Sampler
	{
	public:
		ID3D11SamplerState* SamplerState = nullptr;
	public:
		D3D11Sampler(ID3D11SamplerState* samplerState);
		virtual ~D3D11Sampler();
	};
	class D3D11Texture2D : public Texture2D
	{
	public:
		ID3D11Texture2D* Texture = nullptr;
		ID3D11ShaderResourceView* TextureResourceView = nullptr;
	public:
		D3D11Texture2D(ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureResourceView);
		virtual ~D3D11Texture2D();
	};
}