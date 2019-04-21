#pragma once

#include "JFVKInclude.h"

namespace JFFramework
{
	class JFVKDebug
	{
	public:
		void Setup(VkInstance inst);
		void Free(VkInstance inst);

	private:
		VkDebugReportCallbackEXT msgCallback;

		PFN_vkCreateDebugReportCallbackEXT createDebugReportCallback;
		PFN_vkDestroyDebugReportCallbackEXT destroyDebugReportCallback;
	};
}