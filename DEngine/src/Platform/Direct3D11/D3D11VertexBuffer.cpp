#include "D3D11VertexBuffer.h"

namespace DEngine
{

	Direct3D11Context* D3D11VertexBuffer::graphicsContext = nullptr;
	void D3D11VertexBuffer::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}
	D3D11VertexBuffer::D3D11VertexBuffer(ID3D11Buffer* vb, unsigned int stride) : 
		vertexBuffer(vb), VertexBuffer(stride)
	{

	}
	D3D11VertexBuffer::~D3D11VertexBuffer()
	{
		if (vertexBuffer != nullptr) vertexBuffer->Release();
	}
	void D3D11VertexBuffer::Bind(const unsigned int slot)
	{
		static unsigned int VO = 0;
		graphicsContext->GetDeviceContext()->IASetVertexBuffers(slot, 1, &vertexBuffer, &stride, &VO);
	}
	void D3D11VertexBuffer::UpdateData(void* data, unsigned int size, unsigned int offset)
	{
		D3D11_BOX box;
		ZeroMemory(&box, sizeof(D3D11_BOX));
		box.bottom = 1;
		box.back = 1;
		box.front = 0;
		box.top = 0;
		box.left = offset;
		box.right = offset + size;
		graphicsContext->GetDeviceContext()->UpdateSubresource1(vertexBuffer, 0, &box, data, size, 0, D3D11_COPY_DISCARD);
	}
	void* D3D11VertexBuffer::GetDataPointer(bool wait) const
	{
		D3D11_MAPPED_SUBRESOURCE dms;
		graphicsContext->GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, &dms);
		return dms.pData;
	}
	void D3D11VertexBuffer::ReleaseDataPointer() const
	{
		graphicsContext->GetDeviceContext()->Unmap(vertexBuffer, 0);
	}
}