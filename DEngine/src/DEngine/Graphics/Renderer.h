#pragma once
#include "GraphicsContext.h"
#include "GraphicsFactory.h"
namespace DEngine
{
	class Renderer
	{
	private:
		GraphicsContext* graphicsContext;
		GraphicsFactory* graphicsFactory;
	public:
		Renderer(GraphicsContext* gc, GraphicsFactory* gf);
	};
}

