#pragma once

#include "../Interface/JFSwapChainInterface.h"

#include "JFVKInclude.h"
#include "../../../JFFoundation.h"
#include "../../Platform/JFWindow.h"

#include "JFVKDevice.h"
#include "JFVKImage.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFVKSwapChain : public JFSwapChainInterface
	{
	public:
		JFVKSwapChain(JFVKDevice* device, JFWindow* window);
		~JFVKSwapChain();

	private:
		void CreateSurface();
		void DestroySurface();

		void CreateSwapChain();
		void DestroySwapChain();

		void SetupSupportedFormat();
		void SetupSupportedPresentModes();
		void SetupPresentMode();
		void CreateColorImage();
		void CreateColorImageView();

		uint32_t PresentationSupportedQueueIndex();

	private:
		VkSurfaceKHR surface = VK_NULL_HANDLE;

		VkExtent2D extent;
		VkSwapchainKHR swapChain = VK_NULL_HANDLE;
		JFArray<VkImage> swapChainImages;
		JFArray<VkImageView> swapChainImageViews;

		VkFormat format;
		VkPresentModeKHR presentMode;
		JFArray<VkPresentModeKHR> supportedPresendModes;

		VkSurfaceCapabilitiesKHR capabilities;

		uint32_t desiredNumberOfSwapChainImages;
		VkSurfaceTransformFlagBitsKHR preTransform;

		JFObject<JFWindow> window;
		JFObject<JFVKDevice> device;
	};
}