#pragma once
#include "Vertex.h"
#include "Buffer.h"
namespace DEngine
{
	class Mesh
	{
	private:
		Buffer* m_VertexBuffer;
		Buffer* m_IndexBuffer;
		unsigned int m_IndicesCount;
	public:
		Mesh() = delete;


		Mesh(Buffer* vb, Buffer* ib, unsigned int ic);
		Mesh(const Vertex* vertices, unsigned int verticesCount, const unsigned int* indices, unsigned int indicesCount);
		unsigned int GetIndicesCount();
		virtual void Bind(const unsigned int slot);
		virtual ~Mesh() = default;
	};
}