#pragma once
#include <string>
namespace DEngine
{
	class Window
	{
	protected:
		std::wstring WNDNAME;
		unsigned int width, height;
	public:
		Window(std::wstring windowName, unsigned int _width, unsigned int _height);
		~Window() = default;
	};
}

