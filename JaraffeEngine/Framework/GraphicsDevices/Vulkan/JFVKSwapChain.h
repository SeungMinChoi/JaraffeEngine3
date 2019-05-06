#pragma once

#include "JFVKInclude.h"
#include "../../../JFFoundation.h"
#include "../../Platform/JFWindow.h"

#include "JFVKDevice.h"
#include "JFVKImage.h"
#include "JFVKCommandBuffer.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFVKSwapChain
	{
	public:
		JFVKSwapChain(JFVKDevice* device, JFWindow* window);
		~JFVKSwapChain() noexcept;

		void Prepare();
		void Render();

    public:
        VkSurfaceKHR surface = VK_NULL_HANDLE;

        VkExtent2D extent;
        VkSwapchainKHR swapChain = VK_NULL_HANDLE;

		uint32_t CurrentSwapChainImageIndex = 0;
        JFArray<VkImage> swapChainImages;
        JFArray<VkImageView> swapChainImageViews;

        VkFormat depthFormat = VK_FORMAT_UNDEFINED;
        VkImage depthImage;
        VkImageView depthImageView;
        VkDeviceMemory depthMemory;

		JFArray<VkSurfaceFormatKHR> formats;
        VkFormat format;
        VkPresentModeKHR presentMode;
        JFArray<VkPresentModeKHR> supportedPresendModes;

        VkSurfaceCapabilitiesKHR capabilities;

        uint32_t desiredNumberOfSwapChainImages;
        VkSurfaceTransformFlagBitsKHR preTransform;

		VkRenderPass renderPass;
		JFArray<VkFramebuffer> framebuffers;
		JFArray<JFVKCommandBuffer*> drawCommands;

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

		void CreateDepthImage();
		void CreateDepthImageView();
		void DestroyDepth();

		void SetImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkAccessFlagBits srcAccessMask, const VkCommandBuffer& cmdBuf);

		void CreateRenderPass();
		void CreateFrameBuffer();

		void RecordCommandBuffer(int imageIndex, VkCommandBuffer* cmd);

		uint32_t PresentationSupportedQueueIndex();

    private:
		JFObject<JFWindow> window;
		JFObject<JFVKDevice> device;
	};
}