#include "JFVulkanLayerChecker.h"

using namespace JFFoundation;

bool Framework::JFVulkanLayerChecker::CheckLayer(JFFoundation::JFArray<const char*> layers)
{
	if (layers.Count() <= 0)
		return VK_SUCCESS;

	const JFArray<VkLayerProperties>& layerProperties = LayerProperties();

	// �� ���̾ �����ϴ��� Ȯ�� �մϴ�.
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

	// �� ���̾ �ش��ϴ� Ȯ���ǵ��� ��� �ɴϴ�.
	VkResult result;
	for (const VkLayerProperties& layerProperti : layerProperties)
	{
		uint32_t instanceExtensionCount = 0;
		JFArray<VkExtensionProperties> instanceExtensions;

		// �ش� layer�� �ش��ϴ� Ȯ������ ������ ���ɴϴ�.
		result = vkEnumerateInstanceExtensionProperties(layerProperti.layerName, &instanceExtensionCount, nullptr);

		// Check)
		if (result != VK_SUCCESS || instanceExtensionCount == 0)
			continue;

		// �ش� layer�� �ش��ϴ� Ȯ���� ������ ���ɴϴ�.
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

	// �� ���̾ �ش��ϴ� Ȯ���ǵ��� ��� �ɴϴ�.
	VkResult result;
	for (const VkLayerProperties& layerProperti : layerProperties)
	{
		uint32_t deviceExtensionCount = 0;
		JFArray<VkExtensionProperties> deviceExtensions;

		// �ش� layer�� �ش��ϴ� Ȯ������ ������ ���ɴϴ�.
		result = vkEnumerateDeviceExtensionProperties(*device, layerProperti.layerName, &deviceExtensionCount, nullptr);

		// Check)
		if (result != VK_SUCCESS || deviceExtensionCount == 0)
			continue;

		// �ش� layer�� �ش��ϴ� Ȯ���� ������ ���ɴϴ�.
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

		// 1) �ι�° ���ڸ� null �� �����ؼ� Layer ������ ��� �ɴϴ�.
		VkResult result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);

		// Check)
		assert(result == VK_SUCCESS);
		if (instanceLayerCount == 0)
			return layerProperties;

		// 2) Layer ������ŭ �̸� �迭 ������ �Ҵ� ������ Layer �������� ���ɴϴ�.
		layerProperties.Resize(instanceLayerCount);
		result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties.Data());

		// Check)
		assert(result == VK_SUCCESS);

		return layerProperties;
	};
	static const JFArray<VkLayerProperties> layerProperties(std::move(getLayers()));
	return layerProperties;
}
