#include "D3D11Texture2D.h"

namespace DEngine
{
	D3D11Sampler::D3D11Sampler(ID3D11SamplerState* samplerState) :
		SamplerState(samplerState)
	{

	}
	D3D11Sampler::~D3D11Sampler()
	{
		if (SamplerState != nullptr) SamplerState->Release();
	}
	D3D11Texture2D::D3D11Texture2D(ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureResourceView) : 
		Texture(texture), TextureResourceView(textureResourceView)
	{

	}
	D3D11Texture2D::~D3D11Texture2D()
	{
		if (Texture != nullptr) Texture->Release();
		if (TextureResourceView != nullptr) TextureResourceView->Release();
	}
}