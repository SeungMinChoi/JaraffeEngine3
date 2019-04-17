#include "JFVulkanSwapChain.h"
#include "JFVulkanInclude.h"
#include "JFVulkanDevice.h"
#include "JFVulkanTools.h"

#include "../../Platform/JFWindow.h"

JFFramework::JFVulkanSwapChain::JFVulkanSwapChain(JFWindow* _window, JFVulkanDevice* _device)
	: window(_window)
	, device(_device)
{
}

JFFramework::JFVulkanSwapChain::~JFVulkanSwapChain()
{
}

void JFFramework::JFVulkanSwapChain::InitSurface()
{
#if defined(_WIN32)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandleW(NULL);
	surfaceCreateInfo.hwnd = (HWND)window->Handle();
	VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(device->instance, &surfaceCreateInfo, nullptr, &surface));
#endif
}