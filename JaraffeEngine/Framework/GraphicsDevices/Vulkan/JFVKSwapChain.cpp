#include "JFVKSwapChain.h"
#include "JFVKTools.h"

JFFramework::JFVKSwapChain::JFVKSwapChain(JFVKDevice* _device, JFVKSurface* _surface)
	: device(_device)
	, surface(_surface)
	, swapChain(VK_NULL_HANDLE)
{
	//vkGetPhysicalDeviceSurfaceSupportKHR();
}

JFFramework::JFVKSwapChain::~JFVKSwapChain()
{
}

uint32_t JFFramework::JFVKSwapChain::PresentationSupportedQueueIndex()
{
	uint32_t queueCount = device->queueFamilyCount;

	// queue들이 Present지원하는지 여부를 저장
	JFArray<VkBool32> supportsPresent(queueCount); // (RAII)
	for (uint32_t i = 0; i < queueCount; ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(*device->physicalDevice, i, surface->surface, &supportsPresent[i]);
	}

	// Graphics Queue중에서 Present를 지원하는 Queue를 찾습니다.
	uint32_t presentQueueNodeIndex = UINT32_MAX;
	for (uint32_t i = 0; i < queueCount; ++i)
	{
		if (supportsPresent[i] == VK_FALSE)
			continue;

		if (device->queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			presentQueueNodeIndex = i;
			break;
		}
	}

	// 지원하는 queue가 없으면 일단 크래시
	if (presentQueueNodeIndex == UINT32_MAX)
		assert(false);

	return presentQueueNodeIndex;
}

VkFormat JFFramework::JFVKSwapChain::SupportedFormats()
{
	// FormatCount
	uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(*device->physicalDevice, surface->surface, &formatCount, nullptr);

	// Formats
	JFArray<VkSurfaceFormatKHR> formats(formatCount);
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(*device->physicalDevice, surface->surface, &formatCount, formats.Data()));

	// 일단 책대로.
	// VK_FORMAT_UNDEFINED일 때 화면에 아무것도 없음
	// 32bit RGBA형식을 사용함
	if (formatCount == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
	{
		return VK_FORMAT_B8G8R8A8_UNORM;
	}
	else
	{
		assert(formatCount >= 1);
		return formats[0].format;
	}
}
