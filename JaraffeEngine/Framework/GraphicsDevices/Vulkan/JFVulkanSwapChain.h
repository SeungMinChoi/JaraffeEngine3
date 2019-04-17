#pragma once

#include "../../../JFFoundation.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFWindow;
	class JFVulkanDevice;
	class JFVulkanSwapChain
	{
	public:
		JFVulkanSwapChain(JFWindow* window, JFVulkanDevice* device);
		~JFVulkanSwapChain();

	private:
		void InitSurface();

		VkSurfaceKHR surface;

		JFObject<JFWindow> window;
		JFObject<JFVulkanDevice> device;
	};
}