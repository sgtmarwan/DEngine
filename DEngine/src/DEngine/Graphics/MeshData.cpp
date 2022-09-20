#include "MeshData.h"
namespace DEngine
{
	MeshData::MeshData(Vertex* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount) :
		Vertices(vertices), Indices(indices), VerticesCount(verticesCount), IndicesCount(indicesCount)
	{
	}
}