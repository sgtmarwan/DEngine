#pragma once
#include "VertexBuffer.h"
namespace DEngine
{
	class Mesh
	{
	protected:
		VertexBuffer* VB;
		unsigned int IndicesCount;
	public:
		Mesh(VertexBuffer* vb, unsigned int ic);
		unsigned int GetIndicesCount();
		virtual void Bind(const unsigned int slot) const = 0;
		virtual ~Mesh() = default;

		void VBUpdateData(void* data, unsigned int size, unsigned int offset);
		void* VBGetDataPointer(bool wait) const;
		void VBReleaseDataPointer() const;

		virtual void IBUpdateData(void* data, unsigned int size, unsigned int offset) = 0;
		virtual void* IBGetDataPointer(bool wait) const = 0;
		virtual void IBReleaseDataPointer() const = 0;
	};
}