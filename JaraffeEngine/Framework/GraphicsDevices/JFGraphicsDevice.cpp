#include "../../JFInclude.h"
#include "JFGraphicsDevice.h"
#include "../Platform/JFWindow.h"

#ifdef JF_VULKAN
#	include "Vulkan/JFVKDevice.h"
#	include "Vulkan/JFVKSwapChain.h"
#endif

namespace Private
{
	class JFGraphicsDeviceImpl
	{
	public:
		JFGraphicsDeviceImpl(JFWindow* window)
		{
			device = new JFVKDevice();
			swapChain = new JFVKSwapChain(device, window);
			swapChain->Prepare();
		}

		void Render()
		{
			swapChain->Render();
		}

	private:
		JFVKDevice* device;
		JFVKSwapChain* swapChain;
	};
}

JFFramework::JFGraphicsDevice::JFGraphicsDevice()
{
	
}

JFFramework::JFGraphicsDevice::~JFGraphicsDevice()
{
	
}

void JFFramework::JFGraphicsDevice::Create(JFWindow* window)
{
	impl = new Private::JFGraphicsDeviceImpl(window);
}

void JFFramework::JFGraphicsDevice::Destroy()
{
	delete impl;
	impl = nullptr;
}

void JFFramework::JFGraphicsDevice::Render()
{
	reinterpret_cast<Private::JFGraphicsDeviceImpl*>(impl)->Render();
}
