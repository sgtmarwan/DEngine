#include "D3D11Mesh.h"

namespace DEngine
{
	Direct3D11Context* D3D11Mesh::graphicsContext = nullptr;
	void D3D11Mesh::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}

	D3D11Mesh::D3D11Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, unsigned int indicesCount) : 
		VertexBuffer(vertexBuffer), IndexBuffer(indexBuffer), Mesh(indicesCount)
	{

	}

	void D3D11Mesh::Bind(const unsigned int slot) const
	{
		unsigned int VS = sizeof(Vertex);
		unsigned int VO = 0;
		graphicsContext->GetDeviceContext()->IASetVertexBuffers(slot, 1, &VertexBuffer, &VS, &VO);
		graphicsContext->GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	D3D11Mesh::~D3D11Mesh()
	{
		if (VertexBuffer != nullptr) VertexBuffer->Release();
		if (IndexBuffer != nullptr) IndexBuffer->Release();
	}
}