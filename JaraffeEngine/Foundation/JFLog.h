#pragma once

#include "../JFInclude.h"

// Loggin System 만들기 전까지 임시
namespace JFFoundation
{
	JF_API void JFLog(const char* fmt, ...);
	JF_API void JFLog(const wchar_t* fmt, ...);
}