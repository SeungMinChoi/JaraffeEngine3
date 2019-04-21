#pragma once

#include "JFVulkanInclude.h"

namespace JFFramework
{
	class JFVulkanDevice;
	class JFVulkanSurface;
	class JFVulkanSwapChain
	{
	public:
		JFVulkanSwapChain(JFVulkanDevice* device, JFVulkanSurface* surface);
		~JFVulkanSwapChain();

	private:
		VkSwapchainKHR swapChain;
	};
}