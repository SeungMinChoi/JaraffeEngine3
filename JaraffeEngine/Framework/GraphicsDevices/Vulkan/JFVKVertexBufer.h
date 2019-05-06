#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"
#include "JFVKResource.h"

namespace JFFramework
{
    class JFVKVertexBuffer
    {
    public:
        JFVKVertexBuffer(JFVKDevice* device, JFArray<byte*> vertexData, uint32_t dataStride);
        ~JFVKVertexBuffer();

    private:
		VkVertexInputBindingDescription	inputDescription;
		VkVertexInputAttributeDescription inputAttributeDescription[2];

        JFObject<JFVKDevice> device;
        JFObject<JFVKResource> buffer;
    };
}