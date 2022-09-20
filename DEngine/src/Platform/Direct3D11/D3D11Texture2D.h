#pragma once
#include <d3d11_4.h>
#include "DEngine/Graphics/Texture2D.h"
#include "Direct3D11Context.h"
namespace DEngine {

	DXGI_FORMAT GetTexture2DFormat(DEngine::TEXTURE2D_FORMAT format);
	UINT GetTexture2DPixelSize(DEngine::TEXTURE2D_FORMAT format);
	unsigned int GetPixelSize(DXGI_FORMAT format);


	class D3D11Texture2D : public Texture2D
	{
	private:
		ID3D11Texture2D* m_Texture = nullptr;
		ID3D11ShaderResourceView* m_TextureResourceView = nullptr;
	public:
		D3D11Texture2D(ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureResourceView);
		virtual ~D3D11Texture2D();
		void Update(void* data, unsigned int size, unsigned int offset) override;
		void* Map(bool wait) const override;
		void UnMap() const override;
		void PSSet(unsigned int slot) override;
	};

}