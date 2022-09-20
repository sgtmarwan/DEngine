#include "GraphicsContext.h"

namespace DEngine
{
	GraphicsContext::GraphicsContext(unsigned short backBufferCount, unsigned short vsync) :
		m_BackBufferCount(backBufferCount), m_Vsync(vsync)
	{
	}
}