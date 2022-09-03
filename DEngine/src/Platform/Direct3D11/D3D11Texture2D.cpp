#include "D3D11Texture2D.h"

namespace DEngine
{
	Direct3D11Context* D3D11Sampler::graphicsContext = nullptr;
	void D3D11Sampler::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}
	Direct3D11Context* D3D11Texture2D::graphicsContext = nullptr;
	void D3D11Texture2D::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}

	void D3D11Sampler::PSSet(const unsigned int slot) const
	{
		graphicsContext->GetDeviceContext()->PSSetSamplers(slot, 1, &SamplerState);
	}

	void D3D11Texture2D::PSSet(const unsigned int slot) const
	{
		graphicsContext->GetDeviceContext()->PSSetShaderResources(slot, 1, &TextureResourceView);
	}

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