#pragma once
#include "Shader.h"
#include "GraphicsFactory.h"
namespace DEngine
{
	class Material
	{
	protected:
		static const GraphicsFactory* graphicsFactory;
	public:
		static void SetGraphicsFactory(const GraphicsFactory* gf);
	protected:
		virtual Shader* GetShader();
	public:
		virtual void Bind() = 0;

		virtual ~Material() = default;
	};
}

