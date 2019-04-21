#include "../../../JFFoundation.h"
#include "JFVKDebug.h"

namespace Private
{
	namespace CallbackFuncs
	{
		VKAPI_ATTR VkBool32 VKAPI_CALL messageCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t srcObject,
			size_t location,
			int32_t msgCode,
			const char* pLayerPrefix,
			const char* pMsg,
			void* pUserData)
		{
			JFFoundation::JFLog(pMsg);

			// The return value of this callback controls wether the Vulkan call that caused
			// the validation message will be aborted or not
			// We return VK_FALSE as we DON'T want Vulkan calls that cause a validation message 
			// (and return a VkResult) to abort
			// If you instead want to have calls abort, pass in VK_TRUE and the function will 
			// return VK_ERROR_VALIDATION_FAILED_EXT 
			return VK_FALSE;
		}
	}
}

void JFFramework::JFVKDebug::Setup(VkInstance inst)
{
	createDebugReportCallback = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(inst, "vkCreateDebugReportCallbackEXT"));
	destroyDebugReportCallback = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(inst, "vkDestroyDebugReportCallbackEXT"));

	VkDebugReportCallbackCreateInfoEXT dbgCreateInfo = {};
	dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	dbgCreateInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)Private::CallbackFuncs::messageCallback;
	dbgCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

	VkResult err = createDebugReportCallback(
		inst,
		&dbgCreateInfo,
		nullptr,
		&msgCallback);
	assert(!err);
}

void JFFramework::JFVKDebug::Free(VkInstance inst)
{
	if (msgCallback != VK_NULL_HANDLE)
	{
		destroyDebugReportCallback(inst, msgCallback, nullptr);
	}
}