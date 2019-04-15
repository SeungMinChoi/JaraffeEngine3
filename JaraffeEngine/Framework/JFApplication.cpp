#include "../JFInclude.h"
#include "JFApplication.h"

#include "Platform/JFWindow.h"
#include "GraphicsDevices/JFGraphicsDevice.h"

JFFramework::JFApplication::JFApplication()
{
	_SetupConsole();

	window = new JFWindow();
	graphicsDevice = new JFGraphicsDevice();

	window->Create();
}

JFFramework::JFApplication::~JFApplication()
{
	if (graphicsDevice)
	{
		delete graphicsDevice;
		graphicsDevice = nullptr;
	}

	if (window)
	{
		delete window;
		window = nullptr;
	}

	window->Destroy();
}

void JFFramework::JFApplication::Run()
{
}

void JFFramework::JFApplication::PreUpdate()
{
}

void JFFramework::JFApplication::Update()
{
}

void JFFramework::JFApplication::PostUpdate()
{
}

void JFFramework::JFApplication::Render()
{
}


void JFFramework::JFApplication::_SetupConsole()
{
#if defined(_WIN32)
	//// �ܼ�â ����
	//AllocConsole();
	//// ǥ�� ��� �ڵ� ����
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//
	//DWORD dwByte(0);
	//// ����� ���ڿ�
	//const char* strMsg = "Hello, World!";
	//// ���
	//WriteFile(hConsole, strMsg, strlen(strMsg), &dwByte, NULL);
	//
	//// ������ ( �ٷ� �����ϸ� ��� ����� Ȯ���ϱ⵵ ���� ������ ������ ���߿� ���� �ؾ� ��)
	//FreeConsole();

	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	//FILE *stream;
	//freopen_s(&stream, "CONOUT$", "w+", stdout);
	//freopen_s(&stream, "CONOUT$", "w+", stderr);
	SetConsoleTitle("hi");
#endif
}
