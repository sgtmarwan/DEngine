#pragma once
#include "Shader.h"
namespace DEngine
{
	class GraphicsFactory
	{
	protected:

	public:
		virtual ~GraphicsFactory() = default;
		virtual Shader CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) = 0;
	};
}

