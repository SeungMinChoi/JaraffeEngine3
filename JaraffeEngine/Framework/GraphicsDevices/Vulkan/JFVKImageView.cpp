#include "JFVKImageView.h"

#include "JFVKTools.h"

JFFramework::JFVKImageView::JFVKImageView(JFVKDevice* _device, JFVKImage* _image, VkImageViewCreateInfo& _imageViewInfo)
	: device(_device)
	, image(_image)
{
	_imageViewInfo.image = image->Image();
	VK_CHECK_RESULT(vkCreateImageView(device->device, &_imageViewInfo, NULL, &imageView));
}

JFFramework::JFVKImageView::~JFVKImageView()
{
	vkDestroyImageView(device->device, imageView, NULL);
}
