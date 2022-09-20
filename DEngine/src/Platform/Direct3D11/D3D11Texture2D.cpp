#include "D3D11Texture2D.h"


namespace DEngine
{
	D3D11Texture2D::D3D11Texture2D(ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureResourceView) : 
		m_Texture(texture), m_TextureResourceView(textureResourceView)
	{

	}
	D3D11Texture2D::~D3D11Texture2D()
	{
		if (m_Texture != nullptr) m_Texture->Release();
		if (m_TextureResourceView != nullptr) m_TextureResourceView->Release();
	}
	void D3D11Texture2D::Update(void* data, unsigned int size, unsigned int offset)
	{
		D3D11_TEXTURE2D_DESC td;
		m_Texture->GetDesc(&td);
		D3D11_BOX box;
		box.bottom = td.Height * GetPixelSize(td.Format);
		box.back = 1;
		box.front = 0;
		box.top = 0;
		box.left = 0;
		box.right = td.Width * GetPixelSize(td.Format);
		Direct3D11Context::Get()->GetDeviceContext()->UpdateSubresource1(m_Texture, 0, &box, data, size, 0, D3D11_COPY_DISCARD);
		if (td.MipLevels != 1)
			Direct3D11Context::Get()->GetDeviceContext()->GenerateMips(m_TextureResourceView);
	}
	void* D3D11Texture2D::Map(bool wait) const
	{
		D3D11_MAPPED_SUBRESOURCE dms;
		Direct3D11Context::Get()->GetDeviceContext()->Map(m_Texture, 0, D3D11_MAP_WRITE_DISCARD, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, &dms);
		return dms.pData;
	}
	void D3D11Texture2D::UnMap() const
	{
		Direct3D11Context::Get()->GetDeviceContext()->Unmap(m_Texture, 0);
	}
	void D3D11Texture2D::PSSet(unsigned int slot)
	{
		Direct3D11Context::Get()->GetDeviceContext()->PSSetShaderResources(slot, 1, &m_TextureResourceView);
	}
	DXGI_FORMAT GetTexture2DFormat(DEngine::TEXTURE2D_FORMAT format)
	{
		switch (format)
		{
		case DEngine::TEXTURE2D_FORMAT::RGBA8_UNORM:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		default:
			return DXGI_FORMAT_UNKNOWN;
			break;
		}
	}
	UINT GetTexture2DPixelSize(DEngine::TEXTURE2D_FORMAT format)
	{

		switch (format)
		{
		case DEngine::TEXTURE2D_FORMAT::RGBA8_UNORM:
			return 4;
			break;
		default:
			return 0;
			break;
		}
	}
	unsigned int GetPixelSize(DXGI_FORMAT format)
	{
		switch (format)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			return 4;
			break;
		default:
			return 0;
			break;
		}
	}
}