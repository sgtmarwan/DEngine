#pragma once
#include "Resource.h"
namespace DEngine
{
	enum class BUFFER_TYPE
	{
		VertexBuffer, IndexBuffer, ShaderBuffer
	};


	class Buffer : public Resource
	{
	public:
		virtual ~Buffer() = default;

		virtual void BindIndexBuffer() = 0;
		virtual void BindVertexBuffer(unsigned int slot, unsigned int stride) = 0;

		virtual void VSSet(unsigned int slot) = 0;
		virtual void PSSet(unsigned int slot) = 0;
	};
}