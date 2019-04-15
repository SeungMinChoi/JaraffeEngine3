#pragma once

#include "JFVulkanInclude.h"
#include "../../../JFFoundation.h"

namespace JFFramework
{
	class JFCommandBuffer
	{
	public:
		JFCommandBuffer(const VkDevice* device);

	private:
		VkCommandPool cmdPool;
		JFFoundation::JFArray<VkCommandBuffer> buffers;
	};
}