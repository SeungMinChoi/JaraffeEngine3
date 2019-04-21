#include "JFVulkanSurface.h"
#include "JFVulkanDevice.h"
#include "JFVulkanTools.h"

#include "../../Platform/JFWindow.h"

JFFramework::JFVulkanSurface::JFVulkanSurface(JFWindow* _window, JFVulkanDevice* _device)
	: window(_window)
	, device(_device)
{}

JFFramework::JFVulkanSurface::~JFVulkanSurface()
{}

void JFFramework::JFVulkanSurface::Create()
{
#if defined(_WIN32)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandleW(NULL);
	surfaceCreateInfo.hwnd = (HWND)window->Handle();
	VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(device->instance, &surfaceCreateInfo, nullptr, &surface));
#endif
}

void JFFramework::JFVulkanSurface::Destroy()
{
	vkDestroySurfaceKHR(device->instance, surface, nullptr);
}
