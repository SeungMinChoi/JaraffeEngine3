#include "JFVKSwapChain.h"
#include "JFVKTools.h"

JFFramework::JFVKSwapChain::JFVKSwapChain(JFVKDevice* _device, JFWindow* _window)
	: device(_device)
	, window(_window)
{
	CreateSurface();
	CreateSwapChain();
	//vkGetPhysicalDeviceSurfaceSupportKHR();
}

JFFramework::JFVKSwapChain::~JFVKSwapChain()
{
	DestroySwapChain();
	DestroySurface();
}

uint32_t JFFramework::JFVKSwapChain::PresentationSupportedQueueIndex()
{
	uint32_t queueCount = device->queueFamilyCount;

	// queue들이 Present지원하는지 여부를 저장
	JFArray<VkBool32> supportsPresent(queueCount); // (RAII)
	for (uint32_t i = 0; i < queueCount; ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(*device->physicalDevice, i, surface, &supportsPresent[i]);
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

void JFFramework::JFVKSwapChain::CreateSurface()
{
#if defined(_WIN32)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandleW(NULL);
	surfaceCreateInfo.hwnd = (HWND)window->Handle();
	VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(device->instance, &surfaceCreateInfo, nullptr, &surface));
#endif
}

void JFFramework::JFVKSwapChain::DestroySurface()
{
	vkDestroySurfaceKHR(device->instance, surface, nullptr);
}

void JFFramework::JFVKSwapChain::CreateSwapChain()
{
	SetupSupportedFormat();
	SetupSupportedPresentModes();
	SetupPresentMode();
	CreateColorImage();
	CreateColorImageView();
}

void JFFramework::JFVKSwapChain::DestroySwapChain()
{
}

void JFFramework::JFVKSwapChain::SetupSupportedFormat()
{
	// FormatCount
	uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(*device->physicalDevice, surface, &formatCount, nullptr);

	// Formats
	JFArray<VkSurfaceFormatKHR> formats(formatCount);
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(*device->physicalDevice, surface, &formatCount, formats.Data()));

	// 일단 책대로.
	// VK_FORMAT_UNDEFINED일 때 화면에 아무것도 없음
	// 32bit RGBA형식을 사용함
	if (formatCount == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
	{
		format = VK_FORMAT_B8G8R8A8_UNORM;
	}
	else
	{
		assert(formatCount >= 1);
		format = formats[0].format;
	}
}

void JFFramework::JFVKSwapChain::SetupSupportedPresentModes()
{
	// Capabilites를 얻어온다.
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*device->physicalDevice, surface, &capabilities));

	// Presentmode 개수를 얻어옵니다.
	uint32_t presentModeCount;
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(*device->physicalDevice, surface, &presentModeCount, nullptr));
	assert(presentModeCount > 0);

	supportedPresendModes.Clear();
	supportedPresendModes.Resize(presentModeCount);

	// PresentMode들을 얻어옵니다.
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(*device->physicalDevice, surface, &presentModeCount, supportedPresendModes.Data()));

	// 화면의 폭과 높이가 정의되지 않은 경우 이미지 크기와 동일하게 설정
	if (capabilities.currentExtent.width == (uint32_t)-1)
	{
		// todo : window기능 완성되면 변경예정
		extent.width = (uint32_t)window->size.width;
		extent.height = (uint32_t)window->size.height;
	}
	else
	{
		// 화면의 크기가 정의된 경우 스와프 체인 크기를 맞추어야 한다.
		extent = capabilities.currentExtent;
	}
}

void JFFramework::JFVKSwapChain::SetupPresentMode()
{
	// 사용할 PresentMode를 설정
	presentMode = VK_PRESENT_MODE_FIFO_KHR;
	for (const VkPresentModeKHR& mode : supportedPresendModes)
	{
		// MAILBOX : 가장 지연이 작고, 깨짐이 발생하지 않는 모드.
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		}
		else
		{
			// 차선으로 IMMEDIATE 사용 ( 가장 빠르지만 깨짐발생 )
			if (mode == VK_PRESENT_MODE_IMMEDIATE_KHR)
			{
				presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
			}
		}
	}

	// SwapChain에서 사용할 Image의 수 결정
	desiredNumberOfSwapChainImages = Min(capabilities.minImageCount + 1, capabilities.maxImageCount);

	if (capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}
	else
	{
		preTransform = capabilities.currentTransform;
	}
}

void JFFramework::JFVKSwapChain::CreateColorImage()
{
	VkSwapchainCreateInfoKHR swapChainInfo = {};
	swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapChainInfo.pNext = NULL;
	swapChainInfo.surface = surface;
	swapChainInfo.minImageCount = desiredNumberOfSwapChainImages;
	swapChainInfo.imageFormat = format;
	swapChainInfo.imageExtent.width = extent.width;
	swapChainInfo.imageExtent.height = extent.height;
	swapChainInfo.preTransform = preTransform;
	swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapChainInfo.imageArrayLayers = 1;
	swapChainInfo.presentMode = presentMode;
	swapChainInfo.oldSwapchain = VK_NULL_HANDLE;
	swapChainInfo.clipped = true;
	swapChainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapChainInfo.queueFamilyIndexCount = 0;
	swapChainInfo.pQueueFamilyIndices = NULL;

	VK_CHECK_RESULT(vkCreateSwapchainKHR(device->device, &swapChainInfo, NULL, &swapChain));

	// Create the swapchain object
	uint32_t swapchainImageCount = 0;
	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device->device, swapChain, &swapchainImageCount, NULL));

	swapChainImages.Clear();
	swapChainImages.Resize(swapchainImageCount);

	// Retrieve the swapchain image surfaces 
	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device->device, swapChain, &swapchainImageCount, swapChainImages.Data()));
}

void JFFramework::JFVKSwapChain::CreateColorImageView()
{
	swapChainImageViews.Clear();
	swapChainImageViews.Resize(swapChainImages.Count());
	for (uint32_t i = 0; i < swapChainImageViews.Count(); ++i)
	{
		VkImageViewCreateInfo imgViewInfo = {};
		imgViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imgViewInfo.pNext = NULL;
		imgViewInfo.format = format;
		imgViewInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY };
		imgViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imgViewInfo.subresourceRange.baseMipLevel = 0;
		imgViewInfo.subresourceRange.levelCount = 1;
		imgViewInfo.subresourceRange.baseArrayLayer = 0;
		imgViewInfo.subresourceRange.layerCount = 1;
		imgViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imgViewInfo.flags = 0;
		imgViewInfo.image = swapChainImages[i];

		VK_CHECK_RESULT(vkCreateImageView(device->device, &imgViewInfo, NULL, &swapChainImageViews[i]));
	}
}
