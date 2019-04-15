#include "../../JFInclude.h"
#include "JFVulkanDevice.h"

#include "../../JFFoundation.h"

#include "JFVulkanTools.h"
#include "JFVulkanLayerChecker.h"

using namespace JFFramework;
using namespace JFFoundation;

JFFramework::JFVulkanDevice::JFVulkanDevice()
{
	VK_CHECK_RESULT(_CreateInstance());
	VK_CHECK_RESULT(_CreateDevice());

#ifdef VK_VALIDATION
	debug.Setup(instance);
#endif
}

JFFramework::JFVulkanDevice::~JFVulkanDevice()
{
#ifdef VK_VALIDATION
	debug.Free(instance);
#endif

	_DestroyDevice();
	_DestroyInstance();
}

VkResult JFFramework::JFVulkanDevice::_CreateInstance()
{
	JFArray<const char*> layerNames = { "VK_LAYER_LUNARG_standard_validation" };
	// VK_LAYER_LUNARG_api_dump
	JFArray<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME };
	// VK_EXT_DEBUG_REPORT_EXTENSION_NAME

	// Enable surface extensions depending on os
#if defined(_WIN32)
	instanceExtensions.Add(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
	instanceExtensions.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_DIRECT2DISPLAY)
	instanceExtensions.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	instanceExtensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
	instanceExtensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	instanceExtensions.push_back(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	instanceExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#endif

#ifdef VK_VALIDATION
	instanceExtensions.Add(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
#endif

	if (Framework::JFVulkanLayerChecker::CheckLayer(layerNames) == false)
	{
		JFLog("Layer validation not available!");
	}
	
	if (Framework::JFVulkanLayerChecker::CheckInstanceExtension(instanceExtensions) == false)
	{
		JFLog("InstanceExtension validation not available!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = JFENGINE_NAME;
	appInfo.applicationVersion = 1;
	appInfo.pEngineName = JFENGINE_NAME;
	appInfo.engineVersion = 1;
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pNext = nullptr;
	instanceCreateInfo.flags = 0;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.Count();
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.Data();
	instanceCreateInfo.enabledLayerCount = (uint32_t)layerNames.Count();
	instanceCreateInfo.ppEnabledLayerNames = layerNames.Data();

	return vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
}

void JFFramework::JFVulkanDevice::_DestroyInstance()
{
	vkDestroyInstance(instance, nullptr);
}

VkResult JFFramework::JFVulkanDevice::_CreateDevice()
{
	JFArray<const char*> layerNames = { "VK_LAYER_LUNARG_standard_validation" };
	JFArray<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	uint32_t deviceCount;

	JFArray<VkPhysicalDevice> deviceList;

	VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr));
	assert(deviceCount > 0);

	deviceList.Resize(deviceCount);
	VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, deviceList.Data()));

	// �ϴ� ù��° ����̽�.
	// ���Ŀ� ���ϴ� ��ɵ��� ��� ������ �� �������� �־ ����Ʈ�� ������ �ϰ�
	// ��ɵ鿡 �ʿ��� ��ɵ��� �����ϴ��� ���ο� ���� �׷��� ����� Ȱ��ȭ ���θ� ���ϵ��� ����. ( fallback�� �����ϴ� ���·� �� �� �ֵ��� )
	// ��, �ּ� ����� �־�� ������ ��������.
	//for (VkPhysicalDevice& pd : deviceList)
	VkPhysicalDevice& pd = deviceList[0];
	{
		if (Framework::JFVulkanLayerChecker::CheckDeviceExtension(&pd, deviceExtensions) == false)
		{
			JFLog("Device extension validation not available!");
		}

		// device Features
		vkGetPhysicalDeviceFeatures(pd, &deviceFeatures);
		
		// device properties
		vkGetPhysicalDeviceProperties(pd, &deviceProperties);

		// device Memory Info
		vkGetPhysicalDeviceMemoryProperties(pd, &memoryProperties);

		JFArray<VkQueueFamilyProperties> queueFamilyProps;
		{
			vkGetPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, NULL);

			queueFamilyProps.Resize(queueFamilyCount);

			vkGetPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, queueFamilyProps.Data());
		}

		VkDeviceQueueCreateInfo queueCreateInfo = {};

		graphicsQueueIndex = 0;
		for (const VkQueueFamilyProperties& queueFamilyProperti : queueFamilyProps)
		{
			// ��ǻ��, ����, �׷��Ƚ�, ��� ť�� ������.
			if (queueFamilyProperti.queueFlags & VK_QUEUE_COMPUTE_BIT) 
			{
				++graphicsQueueIndex;
				const float defaultQueuePriority(0.0f);

				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.pNext = NULL;
				queueCreateInfo.queueFamilyIndex = graphicsQueueIndex;
				queueCreateInfo.queueCount = 1;	// �ϳ��� ť �Ӽ��� ť�� ������ �߰�����.
				queueCreateInfo.pQueuePriorities = &defaultQueuePriority;
				break;
			}
		}

		VkDeviceCreateInfo deviceInfo = {};
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pNext = NULL;
		deviceInfo.queueCreateInfoCount = 1;
		deviceInfo.pQueueCreateInfos = &queueCreateInfo;
		deviceInfo.enabledLayerCount = 0;
		deviceInfo.ppEnabledLayerNames = NULL;
		deviceInfo.enabledExtensionCount = (uint32_t)deviceExtensions.Count();
		deviceInfo.ppEnabledExtensionNames = deviceExtensions.Data();
		deviceInfo.pEnabledFeatures = NULL;

		VK_CHECK_RESULT(vkCreateDevice(pd, &deviceInfo, NULL, &device));

		// Queue�� vkCreateDevice�� ���� ��ġ ��ü�� ������ �� ���������� �����˴ϴ�.
		vkGetDeviceQueue(device, graphicsQueueIndex, 0, &queue);
		//vkDeviceWaitIdle(device);

		return VK_SUCCESS;
	}

	return VK_INCOMPLETE;
}

void JFFramework::JFVulkanDevice::_DestroyDevice()
{
	vkDestroyDevice(device, nullptr);
}