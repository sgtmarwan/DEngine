#pragma once

namespace DEngine {

	enum class TEXTURE2D_FOMAT
	{
		RGBA8_UNORM = 0
	};

	class Sampler
	{
	protected:

	public:
		virtual void PSSet(const unsigned int slot) const = 0;
		virtual ~Sampler() = default;
	};
	class Texture2D
	{
	protected:

	public:
		virtual void PSSet(const unsigned int slot) const = 0;
		virtual ~Texture2D() = default;
	};
}