#include "JFVKVertexBufer.h"

JFFramework::JFVKVertexBuffer::JFVKVertexBuffer(JFVKDevice* _device, size_t size)
    : device(_device)
{
    buffer = new JFVKResource(device, 
                              VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                              VK_SHARING_MODE_EXCLUSIVE,
                              size);
}

JFFramework::JFVKVertexBuffer::~JFVKVertexBuffer()
{
}
