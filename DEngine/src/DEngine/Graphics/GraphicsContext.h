#pragma once
namespace DEngine
{
	class GraphicsContext
	{
	protected:
		unsigned short BackBufferCount;
		unsigned short Vsync;
		unsigned short CurrentBackBuffer = 0;
	public:
		virtual ~GraphicsContext() = default;
		GraphicsContext(unsigned short backBufferCount, unsigned short vsync);
		virtual void PresentFrame() = 0;
		virtual void ChangeRes(unsigned int width, unsigned int height) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
	};
}

