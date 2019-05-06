#include "JFVKDevice.h"

#include "JFVKTools.h"
#include "JFVKLayerChecker.h"

using namespace JFFramework;
using namespace JFFoundation;

JFFramework::JFVKDevice::JFVKDevice()
	: device(VK_NULL_HANDLE)
	, instance(VK_NULL_HANDLE)
	, queue(VK_NULL_HANDLE)
	, physicalDevice(nullptr)
{
	VK_CHECK_RESULT(CreateInstance());
	VK_CHECK_RESULT(CreateDevice());

#ifdef VK_VALIDATION
	debug.Setup(instance);
#endif
}

JFFramework::JFVKDevice::~JFVKDevice()
{
#ifdef VK_VALIDATION
	debug.Free(instance);
#endif

	DestroyDevice();
	DestroyInstance();
}

bool JFFramework::JFVKDevice::MemoryTypeFromProperties(uint32_t typeBits, VkFlags requirementsMask, uint32_t * typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < 32; i++)
	{
		if ((typeBits & 1) == 1)
		{
			// Type is available, does it match user properties?
			if ((memoryProperties.memoryTypes[i].propertyFlags & requirementsMask) == requirementsMask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}

	// No memory types matched, return failure
	return false;
}

VkResult JFFramework::JFVKDevice::CreateInstance()
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

	if (Framework::JFVKLayerChecker::CheckLayer(layerNames) == false)
	{
		JFLog("Layer validation not available!");
	}
	
	if (Framework::JFVKLayerChecker::CheckInstanceExtension(instanceExtensions) == false)
	{
		JFLog("InstanceExtension validation not available!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = JFENGINE_NAME;
	appInfo.applicationVersion = 1;
	appInfo.pEngineName = JFENGINE_NAME;
	appInfo.engineVersion = VK_MAKE_VERSION(EngineVersion::Major, EngineVersion::Minor, EngineVersion::Patch);
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

void JFFramework::JFVKDevice::DestroyInstance()
{
	vkDestroyInstance(instance, nullptr);
}

VkResult JFFramework::JFVKDevice::CreateDevice()
{
	JFArray<const char*> layerNames = { "VK_LAYER_LUNARG_standard_validation" };
	JFArray<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	uint32_t deviceCount;

	VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr));
	assert(deviceCount > 0);

	deviceList.Resize(deviceCount);
	VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, deviceList.Data()));

	// 일단 첫번째 디바이스.
	// 이후에 원하는 기능들을 사용 가능할 때 가산점을 주어서 디폴트로 고르도록 하고
	// 기능들에 필요한 기능들을 지원하는지 여부에 따라서 그래픽 기술들 활성화 여부를 정하도록 하자. ( fallback을 지원하는 형태로 할 수 있도록 )
	// 단, 최소 사양은 있어야 구현이 편해질듯.
	//for (VkPhysicalDevice& pd : deviceList)
	VkPhysicalDevice& pd = deviceList[0];
	{
		if (Framework::JFVKLayerChecker::CheckDeviceExtension(&pd, deviceExtensions) == false)
		{
			JFLog("Device extension validation not available!");
		}

		physicalDevice = &pd;

		// device Features
		vkGetPhysicalDeviceFeatures(pd, &deviceFeatures);
		
		// device properties
		vkGetPhysicalDeviceProperties(pd, &deviceProperties);

		// device Memory Info
		vkGetPhysicalDeviceMemoryProperties(pd, &memoryProperties);

		// Get QueueFamailyProps
		{
			vkGetPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, NULL);

			queueFamilyProps.Resize(queueFamilyCount);

			vkGetPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, queueFamilyProps.Data());
		}

		VkDeviceQueueCreateInfo queueCreateInfo = {};

		graphicsQueueIndex = 0;
		for (const VkQueueFamilyProperties& queueFamilyProperti : queueFamilyProps)
		{
			// 컴퓨팅, 전송, 그래픽스, 희소 큐로 나뉜다.
			if (queueFamilyProperti.queueFlags & VK_QUEUE_COMPUTE_BIT) 
			{
				++graphicsQueueIndex;
				const float defaultQueuePriority(0.0f);

				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.pNext = NULL;
				queueCreateInfo.queueFamilyIndex = graphicsQueueIndex;
				queueCreateInfo.queueCount = 1;	// 하나의 큐 속성에 큐를 여러개 추가가능.
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

		VK_CHECK_RESULT(vkCreateDevice(*physicalDevice, &deviceInfo, NULL, &device));

		// Queue는 vkCreateDevice로 논리적 장치 개체가 생성될 때 묵시적으로 생성됩니다.
		vkGetDeviceQueue(device, graphicsQueueIndex, 0, &queue);
		//vkDeviceWaitIdle(device);

		return VK_SUCCESS;
	}

	return VK_INCOMPLETE;
}

void JFFramework::JFVKDevice::DestroyDevice()
{
	vkDestroyDevice(device, nullptr);
}