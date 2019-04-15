#pragma once

#define JFENGINE_NAME "JaraffeEngine"

// for DLL
#ifdef JF_DYNAMIC
#	ifdef JF_EXPORTS
#		define JF_API __declspec(dllexport)
#	else
#		define JF_API __declspec(dllimport)
#	endif
#endif

#ifndef JF_API
#	define JF_API
#endif

//#if !defined(JF_VULKAN) && !defined(JF_METAL)
//#	error Must use Graphics API
//#endif

#ifndef FORCEINLINE
#	if (_MSC_VER >= 1200)
#		define FORCEINLINE __forceinline
#	else
#		define FORCEINLINE __inline __attribute__((always_inline))
#	endif
#endif

#ifndef NOINLINE
#	if (_MSC_VER >= 1200)
#		define NOINLINE __declspec(noinline)
#	else
#		define NOINLINE __attribute__((noinline))
#	endif
#endif

#include <stdio.h>
#include <assert.h>

#if defined(_WIN32)
#	include <windows.h>
#endif