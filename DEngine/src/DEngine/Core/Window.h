#pragma once
#include <string>
#include "DEngine/Graphics/GraphicsContext.h"
#include "DEngine/Input/keyboard.h"
#include "DEngine/Input/mouse.h"
namespace DEngine
{
	class Window
	{
	protected:
		std::wstring WNDNAME;
		int width, height;
		GraphicsContext* graphicsContext = nullptr;
		keyboard* kbd = nullptr;
		mouse* mse = nullptr;
	public:
		Window(std::wstring windowName, unsigned int _width, unsigned int _height);
		virtual void Show() = 0;
		virtual long long Update() = 0;
		void SetGraphicsContext(GraphicsContext* gc);
		void SetKeyboard(keyboard* k);
		void SetMouse(mouse* k);
		unsigned int GetWidth();
		unsigned int GetHeight();
		~Window() = default;
	};
}

