#include "GraphicsContext.h"

namespace DEngine
{
	GraphicsContext::GraphicsContext(unsigned short backBufferCount, unsigned short vsync) :
		BackBufferCount(backBufferCount), Vsync(vsync)
	{
	}
}