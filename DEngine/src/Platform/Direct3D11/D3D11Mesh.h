#pragma once
#include "Direct3D11Context.h"
#include "DEngine/Graphics/Mesh.h"

namespace DEngine
{
	class D3D11Mesh : public Mesh
	{
	private:
	public:
		ID3D11Buffer* VertexBuffer = nullptr;
		ID3D11Buffer* IndexBuffer = nullptr;
	public:
		D3D11Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer,unsigned int indicesCount);
		virtual ~D3D11Mesh();
	};
}