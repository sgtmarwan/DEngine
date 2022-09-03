#include "Window.h"

namespace DEngine
{
	Window::Window(std::wstring windowName, unsigned int _width, unsigned int _height) :
		WNDNAME(windowName), width(_width), height(_height)
	{

	}

	void Window::SetGraphicsContext(GraphicsContext* gc)
	{
		graphicsContext = gc;
	}

	void Window::SetKeyboard(keyboard* k)
	{
		kbd = k;
	}
	void Window::SetMouse(mouse* m)
	{
		 mse = m;
	}

	unsigned int Window::GetWidth()
	{
		return width;
	}
	unsigned int Window::GetHeight()
	{
		return height;
	}
}