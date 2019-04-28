#include "JFVKSurface.h"
#include "JFVKTools.h"

JFFramework::JFVKSurface::JFVKSurface(JFWindow* _window, JFVKDevice* _device)
	: window(_window)
	, device(_device)
	, surface(VK_NULL_HANDLE)
{}

JFFramework::JFVKSurface::~JFVKSurface()
{}

void JFFramework::JFVKSurface::Create()
{
#if defined(_WIN32)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandleW(NULL);
	surfaceCreateInfo.hwnd = (HWND)window->Handle();
	VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(device->instance, &surfaceCreateInfo, nullptr, &surface));
#endif
}

void JFFramework::JFVKSurface::Destroy()
{
	vkDestroySurfaceKHR(device->instance, surface, nullptr);
}
