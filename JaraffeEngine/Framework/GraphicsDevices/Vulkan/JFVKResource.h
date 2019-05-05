#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"

namespace JFFramework
{
    class JFVKResource
    {
    public:
        JFVKResource(JFVKDevice* device, VkBufferUsageFlagBits usage, VkSharingMode mode, size_t size);
        ~JFVKResource() noexcept;

    private:
        VkBuffer buffer;
       
        JFObject<JFVKDevice> device;
    };
}