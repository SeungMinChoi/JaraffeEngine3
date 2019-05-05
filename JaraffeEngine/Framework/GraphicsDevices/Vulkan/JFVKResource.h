#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"

namespace JFFramework
{
    class JFVKResource
    {
    public:
        JFVKResource(JFVKDevice* device, VkBufferUsageFlagBits usage, VkSharingMode mode, JFArray<byte*> data);
        ~JFVKResource() noexcept;

    private:
        VkBuffer buffer;
		VkDeviceMemory memory;
		VkDescriptorBufferInfo bufferInfo;
       
        JFObject<JFVKDevice> device;
    };
}