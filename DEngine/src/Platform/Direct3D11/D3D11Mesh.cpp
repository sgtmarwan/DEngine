#include "D3D11Mesh.h"

namespace DEngine
{
	extern const unsigned int VertexStride = sizeof(Vertex);
	extern const unsigned int VertexOffset = 0;
	Direct3D11Context* D3D11Mesh::graphicsContext = nullptr;


	void D3D11Mesh::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}

	D3D11Mesh::D3D11Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, unsigned int indicesCount) : 
		VertexBuffer(vertexBuffer), IndexBuffer(indexBuffer), Mesh(indicesCount)
	{

	}
	void D3D11Mesh::Bind()
	{
		graphicsContext->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexStride, &VertexOffset);
		graphicsContext->GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
	D3D11Mesh::~D3D11Mesh()
	{
		if (VertexBuffer != nullptr) VertexBuffer->Release();
		if (IndexBuffer != nullptr) IndexBuffer->Release();
	}
}