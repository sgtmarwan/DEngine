#pragma once
#include "DEW.h"
#include "DEngine/Core/Window.h"
namespace DEngine
{
	class WinWindow : public Window
	{
	private:
		const wchar_t* WNDCLSNAME;
		HWND hWnd;
		void CreateWindowClass(HINSTANCE hInst);
		void CreateWindow(HINSTANCE hInst);
	public:
		WinWindow(const wchar_t* windowName, const wchar_t* windowClassName, unsigned int width, unsigned int height);
		~WinWindow();
	private:
		static LRESULT WINAPI setUpMsgPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI directMsgPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT WINAPI MsgPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

