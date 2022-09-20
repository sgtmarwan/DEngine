#pragma once
namespace DEngine
{
	class Sampler
	{
	public:
		virtual ~Sampler() = default;
		virtual void PSSet(unsigned int slot) = 0;
	};
}

