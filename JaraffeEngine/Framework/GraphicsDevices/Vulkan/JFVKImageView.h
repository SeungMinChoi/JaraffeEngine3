#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"
#include "JFVKImage.h"
#include "../../../JFFoundation.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFVKImageView
	{
	public:
		JFVKImageView(JFVKDevice* device, JFVKImage* image, VkImageViewCreateInfo& imageViewInfo);
		~JFVKImageView();

	private:
		VkImageView	imageView = VK_NULL_HANDLE;

		JFObject<JFVKImage> image;
		JFObject<JFVKDevice> device;
	};
}