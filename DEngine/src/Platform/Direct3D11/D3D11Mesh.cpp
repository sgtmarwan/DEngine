#include "D3D11Mesh.h"

namespace DEngine
{

	D3D11Mesh::D3D11Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, unsigned int indicesCount) : 
		VertexBuffer(vertexBuffer), IndexBuffer(indexBuffer), Mesh(indicesCount)
	{

	}
	D3D11Mesh::~D3D11Mesh()
	{
		if (VertexBuffer != nullptr) VertexBuffer->Release();
		if (IndexBuffer != nullptr) IndexBuffer->Release();
	}
}