#pragma once
#include "Direct3D11Context.h"
#include "DEngine/Graphics/Mesh.h"

namespace DEngine
{
	class D3D11Mesh : public Mesh
	{
	private:
		static Direct3D11Context* graphicsContext;
	public:
		static void SetGraphicsContext(Direct3D11Context* gc);
	private:
		ID3D11Buffer* VertexBuffer = nullptr;
		ID3D11Buffer* IndexBuffer = nullptr;
	public:
		virtual void Bind(const unsigned int slot) const override;
		D3D11Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer,unsigned int indicesCount);
		virtual ~D3D11Mesh();
	};
}