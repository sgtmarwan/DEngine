#include "D3D11Buffer.h"

namespace DEngine
{
	D3D11Buffer::D3D11Buffer(ID3D11Buffer* buffer) : 
		m_Buffer(buffer)
	{
	}
	D3D11Buffer::~D3D11Buffer()
	{
		if (m_Buffer != nullptr) m_Buffer->Release();
	}
	void D3D11Buffer::Update(void* data, unsigned int size, unsigned int offset)
	{
		D3D11_BOX box;
		box.bottom = 1;
		box.back = 1;
		box.front = 0;
		box.top = 0;
		box.left = offset;
		box.right = offset + size;
		Direct3D11Context::Get()->GetDeviceContext()->UpdateSubresource1(m_Buffer, 0, &box, data, size, 0, D3D11_COPY_DISCARD);
	}
	void* D3D11Buffer::Map(bool wait) const
	{
		D3D11_MAPPED_SUBRESOURCE dms;
		Direct3D11Context::Get()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, &dms);
		return dms.pData;
	}
	void D3D11Buffer::UnMap() const
	{
		Direct3D11Context::Get()->GetDeviceContext()->Unmap(m_Buffer, 0);
	}
	void D3D11Buffer::BindIndexBuffer()
	{
		Direct3D11Context::Get()->GetDeviceContext()->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0);
	}
	void D3D11Buffer::BindVertexBuffer(unsigned int slot, unsigned int stride)
	{
		UINT offset = 0;
		Direct3D11Context::Get()->GetDeviceContext()->IASetVertexBuffers(slot, 1, &m_Buffer, &stride, &offset);
	}
	void D3D11Buffer::VSSet(unsigned int slot)
	{
		Direct3D11Context::Get()->GetDeviceContext()->VSSetConstantBuffers(slot, 1, &m_Buffer);
	}
	void D3D11Buffer::PSSet(unsigned int slot)
	{
		Direct3D11Context::Get()->GetDeviceContext()->PSSetConstantBuffers(slot, 1, &m_Buffer);
	}
	UINT GetBufferType(BUFFER_TYPE type)
	{
		switch (type)
		{
		case DEngine::BUFFER_TYPE::VertexBuffer:
			return D3D11_BIND_VERTEX_BUFFER;
			break;
		case DEngine::BUFFER_TYPE::IndexBuffer:
			return D3D11_BIND_INDEX_BUFFER;
			break;
		case DEngine::BUFFER_TYPE::ShaderBuffer:
			return D3D11_BIND_CONSTANT_BUFFER;
			break;
		default:
			break;
		}
	}
}