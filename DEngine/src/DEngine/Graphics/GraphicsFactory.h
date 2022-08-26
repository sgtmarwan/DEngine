#pragma once
#include "Shader.h"
namespace DEngine
{
	enum class DATA_USAGE
	{
		GRW = 0, GR, GR_CW
	};
	class GraphicsFactory
	{
	protected:

	public:
		virtual ~GraphicsFactory() = default;
		virtual ShaderData* CreateShaderData(void** data, size_t* size, unsigned int count, DATA_USAGE usage) = 0;
		virtual Shader* CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) = 0;
	};
}

