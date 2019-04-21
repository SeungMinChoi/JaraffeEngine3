#pragma once

#define VK_CHECK_RESULT(result)																			\
{																										\
	if (result != VK_SUCCESS)																			\
	{																									\
		JFFoundation::JFLog("Vk Error code : %d [File : %s, line : %d]", result, __FILE__, __LINE__);	\
		assert(result == VK_SUCCESS);																	\
	}																									\
}