#include "JFVKResource.h"
#include "JFVKTools.h"

JFFramework::JFVKResource::JFVKResource(JFVKDevice* _device, 
                                        VkBufferUsageFlagBits usage, 
                                        VkSharingMode mode, 
                                        size_t size)
    : device(_device)
{
    VkBufferCreateInfo bufInfo = {};
    bufInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufInfo.pNext = nullptr;
    bufInfo.usage = usage;
    bufInfo.size = size;
    bufInfo.queueFamilyIndexCount = 0;
    bufInfo.pQueueFamilyIndices = nullptr;
    bufInfo.sharingMode = mode;
    bufInfo.flags = 0;

    VK_CHECK_RESULT(vkCreateBuffer(device->device, &bufInfo, nullptr, &buffer));
}

JFFramework::JFVKResource::~JFVKResource() noexcept
{
    vkDestroyBuffer(device->device, buffer, nullptr);
}
