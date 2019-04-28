#pragma once

#include "../../../JFEngine.h"

#include "JFVKInclude.h"
#include "../Interface/JFGraphicsDeviceInterface.h"

#include "JFVKDebug.h"

namespace JFFramework
{
	class JFVKDevice : public JFGraphicsDeviceInterface
	{
	public:
		JFVKDevice();
		~JFVKDevice();

		bool MemoryTypeFromProperties(uint32_t typeBits, VkFlags requirementsMask, uint32_t* typeIndex);

		VkDevice device;
		VkInstance instance;

		VkQueue queue;
		uint32_t queueFamilyCount;
		uint32_t graphicsQueueIndex;
		uint32_t graphicsQueueWithPresentIndex;
		JFArray<VkQueueFamilyProperties> queueFamilyProps;

		VkPhysicalDevice* physicalDevice;
		VkPhysicalDeviceFeatures deviceFeatures;
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceMemoryProperties memoryProperties;

	private:
		VkResult CreateInstance();
		void DestroyInstance();

		VkResult CreateDevice();
		void DestroyDevice();

#ifdef VK_VALIDATION
		JFVKDebug debug;
#endif
	};
}