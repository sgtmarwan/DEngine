#pragma once
#include "Vertex.h"
namespace DEngine
{
	class Mesh
	{
	protected:
		unsigned int IndicesCount;
	public:
		Mesh(unsigned int ic);
		unsigned int GetIndicesCount();
		virtual ~Mesh() = default;
	};
}