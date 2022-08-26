#pragma once
#include "Direct3D11Context.h"
#include "DEngine/Graphics/Mesh.h"

namespace DEngine
{
	extern const unsigned int VertexStride;
	extern const unsigned int VertexOffset;

	class D3D11Mesh : public Mesh
	{
	private:
		static Direct3D11Context* graphicsContext;
	private:
		ID3D11Buffer* VertexBuffer = nullptr;
		ID3D11Buffer* IndexBuffer = nullptr;
	public:
		D3D11Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer,unsigned int indicesCount);
		static void SetGraphicsContext(Direct3D11Context* gc);
		virtual ~D3D11Mesh();
		virtual void Bind();
	};
}