#pragma once
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
	};
}

