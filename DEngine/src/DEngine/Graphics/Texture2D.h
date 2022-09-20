#pragma once
#include "Resource.h"

namespace DEngine {

	enum class TEXTURE2D_FORMAT
	{
		RGBA8_UNORM = 0
	};

	class Texture2D : public Resource
	{
	public:
		virtual ~Texture2D() = default;
		virtual void PSSet(unsigned int slot) = 0;
	};
}