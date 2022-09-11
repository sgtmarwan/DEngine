#pragma once
#include "Vertex.h"
namespace DEngine
{
	class MeshData
	{
	private:
		Vertex* Vertices;
		unsigned int* Indices;
		unsigned int VerticesCount;
		unsigned int IndicesCount;
	public:
		MeshData(Vertex* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount);
		Vertex* GetVertices() { return Vertices; }
		unsigned int* GetIndices() { return Indices; }
		unsigned int GetVerticesCount() { return VerticesCount; }
		unsigned int GetIndicesCount() { return IndicesCount; }
	};
}