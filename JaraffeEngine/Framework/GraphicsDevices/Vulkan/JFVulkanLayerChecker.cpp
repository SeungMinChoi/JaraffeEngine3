#include "JFVulkanLayerChecker.h"

using namespace JFFoundation;

bool Framework::JFVulkanLayerChecker::CheckLayer(JFFoundation::JFArray<const char*> layers)
{
	if (layers.Count() <= 0)
		return VK_SUCCESS;

	const JFArray<VkLayerProperties>& layerProperties = LayerProperties();

	// 각 레이어가 존재하는지 확인 합니다.
	for (const char* layer : layers)
	{
		bool find = false;
		for (const VkLayerProperties& layerProperti : layerProperties)
		{
			if (strcmp(layer, layerProperti.layerName) == 0)
			{
				find = true;
				break;
			}
		}

		if (find == false)
		{
			return false;
		}
	}

	return true;
}

bool Framework::JFVulkanLayerChecker::CheckInstanceExtension(JFFoundation::JFArray<const char*> extensions)
{
	if (extensions.Count() <= 0)
		return VK_SUCCESS;

	const JFArray<VkLayerProperties>& layerProperties = LayerProperties();

	JFArray<JFArray<VkExtensionProperties>> allInstanceExtensions;

	// 각 레이어에 해당하는 확장판들을 얻어 옵니다.
	VkResult result;
	for (const VkLayerProperties& layerProperti : layerProperties)
	{
		uint32_t instanceExtensionCount = 0;
		JFArray<VkExtensionProperties> instanceExtensions;

		// 해당 layer에 해당하는 확장판의 개수를 얻어옵니다.
		result = vkEnumerateInstanceExtensionProperties(layerProperti.layerName, &instanceExtensionCount, nullptr);

		// Check)
		if (result != VK_SUCCESS || instanceExtensionCount == 0)
			continue;

		// 해당 layer에 해당하는 확장판 정보를 얻어옵니다.
		instanceExtensions.Resize(instanceExtensionCount);
		result = vkEnumerateInstanceExtensionProperties(layerProperti.layerName, &instanceExtensionCount, instanceExtensions.Data());

		// Check)
		if (result != VK_SUCCESS)
			continue;

		allInstanceExtensions.Add(instanceExtensions);
	}

	for (const char* extension : extensions)
	{
		bool find = false;
		for (JFArray<VkExtensionProperties>& instanceExtensions : allInstanceExtensions)
		{
			for (const VkExtensionProperties& instanceExtension : instanceExtensions)
			{
				if (strcmp(extension, instanceExtension.extensionName) == 0)
				{
					find = true;
					break;
				}
			}
		}

		if (find == false)
		{
			return false;
		}
	}

	return true;
}

bool Framework::JFVulkanLayerChecker::CheckDeviceExtension(VkPhysicalDevice* device, JFFoundation::JFArray<const char*> extensions)
{
	const JFArray<VkLayerProperties>& layerProperties = LayerProperties();

	JFArray<JFArray<VkExtensionProperties>> allDeviceExtensions;

	// 각 레이어에 해당하는 확장판들을 얻어 옵니다.
	VkResult result;
	for (const VkLayerProperties& layerProperti : layerProperties)
	{
		uint32_t deviceExtensionCount = 0;
		JFArray<VkExtensionProperties> deviceExtensions;

		// 해당 layer에 해당하는 확장판의 개수를 얻어옵니다.
		result = vkEnumerateDeviceExtensionProperties(*device, layerProperti.layerName, &deviceExtensionCount, nullptr);

		// Check)
		if (result != VK_SUCCESS || deviceExtensionCount == 0)
			continue;

		// 해당 layer에 해당하는 확장판 정보를 얻어옵니다.
		deviceExtensions.Resize(deviceExtensionCount);
		result = vkEnumerateDeviceExtensionProperties(*device, layerProperti.layerName, &deviceExtensionCount, deviceExtensions.Data());

		// Check)
		if (result != VK_SUCCESS)
			continue;

		allDeviceExtensions.Add(std::move(deviceExtensions));
	}

	for (const char* extension : extensions)
	{
		bool find = false;
		for (JFArray<VkExtensionProperties>& instanceExtensions : allDeviceExtensions)
		{
			for (const VkExtensionProperties& instanceExtension : instanceExtensions)
			{
				if (strcmp(extension, instanceExtension.extensionName) == 0)
				{
					find = true;
					break;
				}
			}
		}

		if (find == false)
		{
			return false;
		}
	}

	return true;
}

const JFArray<VkLayerProperties>& Framework::JFVulkanLayerChecker::LayerProperties()
{
	auto getLayers = []() -> JFArray<VkLayerProperties>
	{
		uint32_t instanceLayerCount = 0;
		JFArray<VkLayerProperties> layerProperties;

		// 1) 두번째 인자를 null 로 설정해서 Layer 개수를 얻어 옵니다.
		VkResult result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);

		// Check)
		assert(result == VK_SUCCESS);
		if (instanceLayerCount == 0)
			return layerProperties;

		// 2) Layer 개수만큼 미리 배열 공간을 할당 받은뒤 Layer 정보들을 얻어옵니다.
		layerProperties.Resize(instanceLayerCount);
		result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties.Data());

		// Check)
		assert(result == VK_SUCCESS);

		return layerProperties;
	};
	static const JFArray<VkLayerProperties> layerProperties(std::move(getLayers()));
	return layerProperties;
}
