#include "JFVKSwapChain.h"
#include "JFVKCommandBuffer.h"
#include "JFVKMemory.h"
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

	CreateDepthImage();
	CreateDepthImageView();
}

void JFFramework::JFVKSwapChain::DestroySwapChain()
{
	DestroyDepth();

	for (uint32_t i = 0; i < swapChainImageViews.Count(); ++i)
	{
		vkDestroyImageView(device->device, swapChainImageViews[i], NULL);
	}
	vkDestroySwapchainKHR(device->device, swapChain, NULL);

	vkDestroySurfaceKHR(device->instance, surface, NULL);
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

void JFFramework::JFVKSwapChain::CreateDepthImage()
{
	VkImageCreateInfo imageInfo = {};

	// 깊이 포맷이 정의되지 않은 경우 16bit 값을 사용
	if(depthFormat == VK_FORMAT_UNDEFINED)
		depthFormat = VK_FORMAT_D16_UNORM;

	VkFormatProperties props;
	vkGetPhysicalDeviceFormatProperties(*device->physicalDevice, depthFormat, &props);
	if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
	{
		imageInfo.tiling = VK_IMAGE_TILING_LINEAR;
	}
	else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
	{
		imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	}
	else
	{
		// 원하는 depthBuffer tiling형식을 지원 못함
		exit(-1);
	}

	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.pNext = NULL;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.format = depthFormat;
	imageInfo.extent.width = (uint32_t)window->size.width;
	imageInfo.extent.height = (uint32_t)window->size.height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.queueFamilyIndexCount = 0;
	imageInfo.pQueueFamilyIndices = NULL;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	imageInfo.flags = 0;

	VK_CHECK_RESULT(vkCreateImage(device->device, &imageInfo, NULL, &depthImage));
}

void JFFramework::JFVKSwapChain::CreateDepthImageView()
{
	VkMemoryRequirements memRqrmnt;
	vkGetImageMemoryRequirements(device->device, depthImage, &memRqrmnt);

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAlloc.pNext = NULL;
	memAlloc.allocationSize = 0;
	memAlloc.memoryTypeIndex = 0;
	memAlloc.allocationSize = memRqrmnt.size;
	// Determine the type of memory required with the help of memory properties
	JFVKMemory::MemoryTypeFromProperties(device, memRqrmnt.memoryTypeBits, 0, &memAlloc.memoryTypeIndex);

	// Allocate the memory for image objects
	VK_CHECK_RESULT(vkAllocateMemory(device->device, &memAlloc, NULL, &depthMemory));

	// Bind the allocated memeory
	VK_CHECK_RESULT(vkBindImageMemory(device->device, depthImage, depthMemory, 0));

	VkImageViewCreateInfo imgViewInfo = {};
	imgViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imgViewInfo.pNext = NULL;
	imgViewInfo.image = VK_NULL_HANDLE;
	imgViewInfo.format = depthFormat;
	imgViewInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY };
	imgViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	imgViewInfo.subresourceRange.baseMipLevel = 0;
	imgViewInfo.subresourceRange.levelCount = 1;
	imgViewInfo.subresourceRange.baseArrayLayer = 0;
	imgViewInfo.subresourceRange.layerCount = 1;
	imgViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imgViewInfo.flags = 0;

	if (depthFormat == VK_FORMAT_D16_UNORM_S8_UINT ||
		depthFormat == VK_FORMAT_D24_UNORM_S8_UINT ||
		depthFormat == VK_FORMAT_D32_SFLOAT_S8_UINT)
	{
		imgViewInfo.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	// Use command buffer to create the depth image. This includes -
	// Command buffer allocation, recording with begin/end scope and submission.
	JFVKCommandBuffer cmd(device);
	JFArray<VkCommandBuffer>& cmdBuffers = cmd.Begin(1);
	{
		// Set the image layout to depth stencil optimal
		SetImageLayout(depthImage,
					   imgViewInfo.subresourceRange.aspectMask,
					   VK_IMAGE_LAYOUT_UNDEFINED,
					   VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, (VkAccessFlagBits)0, cmdBuffers[0]);
	}
	cmd.End();
	cmd.Submit();

	// Create the image view and allow the application to use the images.
	imgViewInfo.image = depthImage;
	VK_CHECK_RESULT(vkCreateImageView(device->device, &imgViewInfo, NULL, &depthImageView));
}

void JFFramework::JFVKSwapChain::DestroyDepth()
{
	vkDestroyImageView(device->device, depthImageView, NULL);
	vkDestroyImage(device->device, depthImage, NULL);
	vkFreeMemory(device->device, depthMemory, NULL);
}

void JFFramework::JFVKSwapChain::SetImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkAccessFlagBits srcAccessMask, const VkCommandBuffer& cmdBuf)
{
	VkImageMemoryBarrier imgMemoryBarrier = {};
	imgMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	imgMemoryBarrier.pNext = NULL;
	imgMemoryBarrier.srcAccessMask = srcAccessMask;
	imgMemoryBarrier.dstAccessMask = 0;
	imgMemoryBarrier.oldLayout = oldImageLayout;
	imgMemoryBarrier.newLayout = newImageLayout;
	imgMemoryBarrier.image = image;
	imgMemoryBarrier.subresourceRange.aspectMask = aspectMask;
	imgMemoryBarrier.subresourceRange.baseMipLevel = 0;
	imgMemoryBarrier.subresourceRange.levelCount = 1;
	imgMemoryBarrier.subresourceRange.layerCount = 1;

	if (oldImageLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
	{
		imgMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	}

	switch (newImageLayout)
	{
		// Ensure that anything that was copying from this image has completed
		// An image in this layout can only be used as the destination operand of the commands
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
	case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
		imgMemoryBarrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		break;

		// Ensure any Copy or CPU writes to image are flushed
		// An image in this layout can only be used as a read-only shader resource
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		imgMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
		imgMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		break;

		// An image in this layout can only be used as a framebuffer color attachment
	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		imgMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		break;

		// An image in this layout can only be used as a framebuffer depth/stencil attachment
	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		imgMemoryBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
		break;
	}

	VkPipelineStageFlags srcStages = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
	VkPipelineStageFlags destStages = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

	vkCmdPipelineBarrier(cmdBuf, srcStages, destStages, 0, 0, NULL, 0, NULL, 1, &imgMemoryBarrier);
}
