#include "JFVKImage.h"

#include "JFVKTools.h"
#include "JFVKCommandBuffer.h"

JFFramework::JFVKImage::JFVKImage(JFVKDevice* _device, VkImageCreateInfo& imageInfo)
	: device(_device)
{
	VK_CHECK_RESULT(vkCreateImage(device->device, &imageInfo, nullptr, &image));
}

JFFramework::JFVKImage::~JFVKImage()
{
	vkDestroyImage(device->device, image, nullptr);
}

VkImage JFFramework::JFVKImage::Image()
{
	return image;
}