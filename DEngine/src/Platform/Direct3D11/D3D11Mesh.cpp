#include "D3D11Mesh.h"

namespace DEngine
{
	Direct3D11Context* D3D11Mesh::graphicsContext = nullptr;
	void D3D11Mesh::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}

	D3D11Mesh::D3D11Mesh(VertexBuffer* vertexBuffer, ID3D11Buffer* indexBuffer, unsigned int indicesCount) :
		IndexBuffer(indexBuffer), Mesh(vertexBuffer, indicesCount)
	{

	}

	void D3D11Mesh::Bind(const unsigned int slot) const
	{
		VB->Bind(slot);
		graphicsContext->GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	D3D11Mesh::~D3D11Mesh()
	{
		if (IndexBuffer != nullptr) IndexBuffer->Release();
	}

	void D3D11Mesh::IBUpdateData(void* data, unsigned int size, unsigned int offset)
	{
		D3D11_BOX box;
		ZeroMemory(&box, sizeof(D3D11_BOX));
		box.bottom = 1;
		box.back = 1;
		box.front = 0;
		box.top = 0;
		box.left = offset;
		box.right = offset + size;
		graphicsContext->GetDeviceContext()->UpdateSubresource1(IndexBuffer, 0, &box, data, size, 0, D3D11_COPY_DISCARD);
	}
	void* D3D11Mesh::VBGetDataPointer(bool wait) const
	{
		D3D11_MAPPED_SUBRESOURCE dms;
		graphicsContext->GetDeviceContext()->Map(IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, &dms);
		return dms.pData;
	}
	void D3D11Mesh::VBReleaseDataPointer() const
	{
		graphicsContext->GetDeviceContext()->Unmap(IndexBuffer, 0);
	}
}