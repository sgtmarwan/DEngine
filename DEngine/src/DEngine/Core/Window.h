#pragma once
#include <string>
#include "DEngine/Graphics/GraphicsContext.h"
namespace DEngine
{
	class Window
	{
	protected:
		std::wstring WNDNAME;
		unsigned int width, height;
		GraphicsContext* graphicsContext = nullptr;
	public:
		Window(std::wstring windowName, unsigned int _width, unsigned int _height);
		virtual void Show() = 0;
		virtual long long Update() = 0;
		void SetGraphicsContext(GraphicsContext* gc);
		~Window() = default;
	};
}

