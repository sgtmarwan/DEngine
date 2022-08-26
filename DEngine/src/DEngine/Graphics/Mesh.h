#pragma once
#include "Vertex.h"
#include "GraphicsContext.h"
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
		virtual void Bind() = 0;
	};
}