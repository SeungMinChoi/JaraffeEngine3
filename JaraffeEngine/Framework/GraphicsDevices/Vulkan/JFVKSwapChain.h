#pragma once

#include "JFVKInclude.h"

namespace JFFramework
{
	class JFVKDevice;
	class JFVKSurface;
	class JFVKSwapChain
	{
	public:
		JFVKSwapChain(JFVKDevice* device, JFVKSurface* surface);
		~JFVKSwapChain();

	private:
		VkSwapchainKHR swapChain;
	};
}