#pragma once
namespace DEngine
{
	class Resource
	{
	public:
		virtual void Update(void* data, unsigned int size, unsigned int offset) = 0;
		virtual void* Map(bool wait) const = 0;
		virtual void UnMap() const = 0;
	};
}

