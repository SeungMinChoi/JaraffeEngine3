#include "../../JFInclude.h"
#include "JFGraphicsDevice.h"
#include "Interface/JFSwapChainInterface.h"
#include "Interface/JFGraphicsDeviceInterface.h"
#include "../Platform/JFWindow.h"

#ifdef JF_VULKAN
#	include "Vulkan/JFVKDevice.h"
#	include "Vulkan/JFVKSwapChain.h"
#endif

namespace DeviceHelper
{
	static JFFramework::JFGraphicsDeviceInterface* CreateGraphicsAPI()
	{
#ifdef JF_VULKAN
		return new JFFramework::JFVKDevice();
#else
		return nullptr;
#endif
	}

	static JFFramework::JFSwapChainInterface* CreateSwapChain(JFGraphicsDeviceInterface* device, JFWindow* window)
	{
#ifdef JF_VULKAN
		return new JFFramework::JFVKSwapChain((JFVKDevice*)device, window);
#else
		return nullptr;
#endif
	}
}

JFFramework::JFGraphicsDevice::JFGraphicsDevice()
{
	
}

JFFramework::JFGraphicsDevice::~JFGraphicsDevice()
{
	
}

void JFFramework::JFGraphicsDevice::Create(JFWindow* window)
{
	device = DeviceHelper::CreateGraphicsAPI();
	swapChain = DeviceHelper::CreateSwapChain(device, window);
}

void JFFramework::JFGraphicsDevice::Destroy()
{
	delete swapChain;
	delete device;
}
