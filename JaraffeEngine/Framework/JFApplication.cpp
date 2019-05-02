#include "../JFInclude.h"
#include "JFApplication.h"

JFFramework::JFApplication::JFApplication()
	: window(new JFWindow())
	, graphicsDevice(new JFGraphicsDevice())
{
	SetupConsole();
	window->Create();
	graphicsDevice->Create(window);
}

JFFramework::JFApplication::~JFApplication()
{
	graphicsDevice->Destroy();
	window->Destroy();
	DestroyConsole();
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


void JFFramework::JFApplication::SetupConsole()
{
#if defined(_WIN32)
	//// 콘솔창 생성
	//AllocConsole();
	//// 표준 출력 핸들 얻음
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//
	//DWORD dwByte(0);
	//// 출력할 문자열
	//const char* strMsg = "Hello, World!";
	//// 출력
	//WriteFile(hConsole, strMsg, strlen(strMsg), &dwByte, NULL);
	//
	//// 해제시 ( 바로 해제하면 출력 결과를 확인하기도 전에 없어져 버리니 나중에 해제 해야 함)
	//FreeConsole();

	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	//FILE *stream;
	//freopen_s(&stream, "CONOUT$", "w+", stdout);
	//freopen_s(&stream, "CONOUT$", "w+", stderr);
	SetConsoleTitle("hi");
#endif
}

void JFFramework::JFApplication::DestroyConsole()
{
	FreeConsole();
}