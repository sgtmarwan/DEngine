#include "Mesh.h"

#include "GraphicsFactory.h"
namespace DEngine
{

	Mesh::Mesh(Buffer* vb, Buffer* ib, unsigned int ic) :
		m_VertexBuffer(vb), m_IndexBuffer(ib), m_IndicesCount(ic)
	{
	}

	Mesh::Mesh(const Vertex* vertices, unsigned int verticesCount, const unsigned int* indices, unsigned int indicesCount) : 
		m_IndicesCount(indicesCount)
	{
		m_VertexBuffer = GraphicsFactory::Get()->CreateBuffer(vertices, verticesCount * sizeof(Vertex), DATA_USAGE::GRW, BUFFER_TYPE::VertexBuffer);
		m_IndexBuffer = GraphicsFactory::Get()->CreateBuffer(indices, indicesCount * sizeof(unsigned int), DATA_USAGE::GRW, BUFFER_TYPE::IndexBuffer);
	}

	unsigned int Mesh::GetIndicesCount()
	{
		return m_IndicesCount;
	}

	void Mesh::Bind(const unsigned int slot)
	{
		m_VertexBuffer->BindVertexBuffer(slot, sizeof(Vertex));
		m_IndexBuffer->BindIndexBuffer();
	}
}