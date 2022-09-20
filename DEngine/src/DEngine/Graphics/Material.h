#pragma once
#include "Shader.h"
#include "GraphicsFactory.h"
namespace DEngine
{
	class Material
	{
	protected:
		virtual unsigned int GetShaderId() =  0;
	public:
		virtual void Bind() = 0;

		virtual ~Material() = default;
	};
}

