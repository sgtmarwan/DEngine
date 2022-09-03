#include "WinWindow.h"
namespace DEngine
{
	void WinWindow::Show()
	{
		ShowWindow(hWnd, 1);
	}

	long long WinWindow::Update()
	{
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		switch (msg.message)
		{
		case WM_QUIT:
			return msg.wParam;
			break;
		default:
			return 1;
			break;
		}
	}

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

	HWND& WinWindow::GetWindowHandle()
	{
		return hWnd;
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
			width = LOWORD(lParam);
			height = HIWORD(lParam);
			graphicsContext->Resize(width, height);
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (!(lParam & 0x40000000) || kbd->AutoRepeat)
				kbd->OnKeyDown(static_cast<unsigned char>(wParam));
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			kbd->OnKeyUp(static_cast<unsigned char>(wParam));
			break;
		case WM_CHAR:
			kbd->OnChar(static_cast<char>(wParam));
			break;
		case WM_KILLFOCUS:
			kbd->ClearState();
			break;
		case WM_MOUSEMOVE:
		{
			const POINTS pt = MAKEPOINTS(lParam);

			float x = float(pt.x) / float(width);
			float y = float(pt.y) / float(height);
			if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
			{
				mse->OnMove(x, y);
				if (!mse->IsInWindow())
				{
					SetCapture(hWnd);
					mse->OnEnter();
				}
			}

			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					mse->OnMove(x, y);
				}

				else
				{
					ReleaseCapture();
					mse->OnLeave();
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			SetForegroundWindow(hWnd);
			const POINTS pt = MAKEPOINTS(lParam);

			float x = float(pt.x) / float(width);
			float y = float(pt.y) / float(height);
			mse->OnButtonDown(x, y, 0);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);

			float x = float(pt.x) / float(width);
			float y = float(pt.y) / float(height);
			mse->OnButtonDown(x, y, 1);
			break;
		}
		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);

			float x = float(pt.x) / float(width);
			float y = float(pt.y) / float(height);
			mse->OnButtonUp(x, y, 0);

			if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
			{
				ReleaseCapture();
				mse->OnLeave();
			}
			break;
		}
		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);

			float x = float(pt.x) / float(width);
			float y = float(pt.y) / float(height);
			mse->OnButtonUp(x, y, 1);

			if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
			{
				ReleaseCapture();
				mse->OnLeave();
			}
			break;
		}
		default:
			break;
		}
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
}