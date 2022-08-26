#pragma once
#include "GraphicsContext.h"
#include "INPUT_LAYOUT.h"
namespace DEngine
{
	struct ShaderData
	{
		unsigned int DataCount;
		virtual ~ShaderData() = default;
	};

	class Shader
	{
	protected:

	public:
		virtual ~Shader() = default;
		virtual void Bind() = 0;
		virtual void SetVSShaderData(ShaderData* data, unsigned int startIndex) = 0;
		virtual void SetPSShaderData(ShaderData* data, unsigned int startIndex) = 0;
	};
}

