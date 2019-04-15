#ifdef _WIN32

#include "../JFWindow.h"
#include "../../../JFInclude.h"
#include "../../../JFFoundation.h"

namespace JFFramework
{
	namespace Private
	{
		class Win32Impl
		{
		public:
			HWND hWnd;
		};

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_CLOSE:
				DestroyWindow(hWnd);
				break;

			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}

			return 0;
		}
	}
}

using namespace JFFramework;
using namespace JFFoundation;

JFFramework::JFWindow::JFWindow()
{
	impl = new Private::Win32Impl();
}

JFFramework::JFWindow::~JFWindow()
{
	if (impl)
	{
		delete impl;
		impl = nullptr;
	}
}

void JFFramework::JFWindow::Create()
{
	// CreateWindow 
	// https://docs.microsoft.com/en-us/windows/desktop/learnwin32/closing-the-window

	// GetModuleHandleW
	// Hint : https://bobobobo.wordpress.com/2008/02/03/getting-the-hwnd-and-hinstance-of-the-console-window/
	// Msdn : https://docs.microsoft.com/en-us/windows/desktop/api/libloaderapi/nf-libloaderapi-getmodulehandlew

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Private::WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandleW(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = JFENGINE_NAME;
	wc.lpszClassName = JFENGINE_NAME;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		JFLog("Could not register window class!");
		exit(1);
	}

	HWND hWnd = CreateWindowEx(0, 
						  JFENGINE_NAME,
						  JFENGINE_NAME,
						  WS_CAPTION | WS_SYSMENU,
						  CW_USEDEFAULT, 
						  CW_USEDEFAULT, 
						  CW_USEDEFAULT, 
						  CW_USEDEFAULT,
						  NULL, 
						  NULL, 
						  GetModuleHandleW(NULL), 
						  0);

	if (!hWnd)
	{
		JFLog("Could not create window!");
		exit(1);
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	auto win32 = reinterpret_cast<Private::Win32Impl*>(impl);
	win32->hWnd = hWnd;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void JFFramework::JFWindow::Destroy()
{
	auto win32 = reinterpret_cast<Private::Win32Impl*>(impl);
	PostMessageW(win32->hWnd, WM_CLOSE, 0, 0);
}

#endif