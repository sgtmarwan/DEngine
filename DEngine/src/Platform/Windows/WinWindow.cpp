#include "WinWindow.h"
namespace DEngine
{
	void WinWindow::CreateWindowClass(HINSTANCE hInst)
	{
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.hInstance = hInst;
		wc.lpfnWndProc = &setUpMsgPrc;
		wc.hbrBackground = NULL;
		wc.hIcon = ::LoadIcon(hInst, NULL);
		wc.hIconSm = ::LoadIcon(hInst, NULL);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpszClassName = WNDCLSNAME;
		wc.lpszMenuName = NULL;
		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		if (!RegisterClassEx(&wc))
		{
			MessageBoxEx(NULL, L"Failled to register window class", NULL, MB_OK, NULL);
			return;
		}
	}

	void WinWindow::CreateWindow(HINSTANCE hInst)
	{
		RECT windowRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
		AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW /* | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX*/, false, 0);
		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;
		hWnd = CreateWindowExW(0, WNDCLSNAME, WNDNAME.c_str(), WS_OVERLAPPEDWINDOW /* | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX */, CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, 0, 0, hInst, this);
		if (hWnd == 0)
		{
			MessageBoxExW(NULL, L"Failled to Create Window", NULL, MB_OK, NULL);
			return;
		}
	}

	WinWindow::WinWindow(const wchar_t* windowName, const wchar_t* windowClassName, unsigned int width, unsigned int height) :
		Window(windowName, width, height), WNDCLSNAME(windowClassName)
	{
		CreateWindowClass(GetModuleHandle(NULL));
		CreateWindow(GetModuleHandle(NULL));
	}

	WinWindow::~WinWindow()
	{
		UnregisterClass(WNDCLSNAME, GetModuleHandle(NULL));
		DestroyWindow(hWnd);
	}

	LRESULT __stdcall WinWindow::setUpMsgPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE)
		{
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&directMsgPrc);
			return directMsgPrc(hwnd, msg, wParam, lParam);
		}
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}

	LRESULT __stdcall WinWindow::directMsgPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		WinWindow* const wnd = (WinWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		return wnd->MsgPrc(hwnd, msg, wParam, lParam);
	}

	LRESULT __stdcall WinWindow::MsgPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_SIZE:
			//TODO: Handle Window Resize
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
}