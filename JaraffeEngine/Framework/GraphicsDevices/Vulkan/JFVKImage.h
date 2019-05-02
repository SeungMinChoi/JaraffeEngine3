#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"
#include "../../../JFFoundation.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFVKImage
	{
	public:
		JFVKImage(JFVKDevice* device, VkImageCreateInfo& imageInfo);
		~JFVKImage();

		VkImage Image();

	public:
		VkImage image = VK_NULL_HANDLE;

		JFObject<JFVKDevice> device;
	};
}