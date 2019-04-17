#pragma once

#include "JFVulkanInclude.h"
#include "../Interface/JFGraphicsDeviceInterface.h"

#include "JFVulkanDebug.h"

namespace JFFramework
{
	class JFVulkanDevice : public JFGraphicsDeviceInterface
	{
	public:
		JFVulkanDevice();
		~JFVulkanDevice();

		VkDevice device;
		VkInstance instance;

	private:
		VkResult CreateInstance();
		void DestroyInstance();

		VkResult CreateDevice();
		void DestroyDevice();
	
		VkPhysicalDevice* physicalDevice;
		VkPhysicalDeviceFeatures deviceFeatures;
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceMemoryProperties memoryProperties;

		VkQueue queue;
		uint32_t queueFamilyCount;
		uint32_t graphicsQueueIndex;
		uint32_t graphicsQueueWithPresentIndex;

#ifdef VK_VALIDATION
		JFVulkanDebug debug;
#endif
	};
}