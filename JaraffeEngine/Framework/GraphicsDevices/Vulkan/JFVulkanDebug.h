#pragma once

#include "JFVulkanInclude.h"

namespace JFFramework
{
	class JFVulkanDebug
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