#pragma once

#include "JFVulkanInclude.h"
#include "../../../JFFoundation.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFWindow;
	class JFVulkanDevice;
	class JFVulkanSurface
	{
	public:
		JFVulkanSurface(JFWindow* window, JFVulkanDevice* device);
		~JFVulkanSurface();

		void Create();
		void Destroy();

	private:
		VkSurfaceKHR surface;

		JFObject<JFWindow> window;
		JFObject<JFVulkanDevice> device;
	};
}