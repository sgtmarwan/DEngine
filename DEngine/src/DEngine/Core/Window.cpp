#include "Window.h"

namespace DEngine
{
	Window::Window(std::wstring windowName, unsigned int _width, unsigned int _height) :
		WNDNAME(windowName), width(_width), height(_height)
	{

	}
}