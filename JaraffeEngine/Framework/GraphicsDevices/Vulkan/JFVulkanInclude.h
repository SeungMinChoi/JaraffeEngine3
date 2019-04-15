#pragma once

#define VK_PROTOTYPES

#if defined(_WIN32)
#	define VK_USE_PLATFORM_WIN32_KHR
#endif

// test
#define VK_VALIDATION

#include "vulkan/vulkan.h"