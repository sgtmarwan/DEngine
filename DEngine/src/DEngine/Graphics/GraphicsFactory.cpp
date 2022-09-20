#include "GraphicsFactory.h"

namespace DEngine
{
	GraphicsFactory* GraphicsFactory::s_GraphicsFactory = nullptr;

	void GraphicsFactory::Set(GraphicsFactory* gf)
	{
		s_GraphicsFactory = gf;
	}
	GraphicsFactory* GraphicsFactory::Get()
	{
		return s_GraphicsFactory;
	}
}