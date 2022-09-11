#pragma once
#include "Vertex.h"
namespace DEngine
{
	class VertexBuffer
	{
	protected:
		unsigned int stride;
	public:
		VertexBuffer(unsigned int _stride) :
			stride(_stride)
		{

		}
		virtual ~VertexBuffer() = default;
		virtual void Bind(const unsigned int slot) = 0;
		virtual void UpdateData(void* data, unsigned int size, unsigned int offset) = 0;
		virtual void* GetDataPointer(bool wait) const = 0;
		virtual void ReleaseDataPointer() const = 0;
	};
}