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
		virtual void Bind(const unsigned int slot) const = 0;
		virtual ~Mesh() = default;
	};
}