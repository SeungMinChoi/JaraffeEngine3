#include "../../JFInclude.h"
#include "JFGraphicsDevice.h"
#include "Interface/JFGraphicsDeviceInterface.h"

#ifdef JF_VULKAN
#	include "Vulkan/JFVulkanDevice.h"
#endif

namespace DeviceHelper
{
	static JFFramework::JFGraphicsDeviceInterface* CreateGraphicsAPI()
	{
#ifdef JF_VULKAN
		return new JFFramework::JFVulkanDevice();
#else
		return nullptr;
#endif
	}
}

JFFramework::JFGraphicsDevice::JFGraphicsDevice()
{
	device = DeviceHelper::CreateGraphicsAPI();
}

JFFramework::JFGraphicsDevice::~JFGraphicsDevice()
{
	delete device;
}