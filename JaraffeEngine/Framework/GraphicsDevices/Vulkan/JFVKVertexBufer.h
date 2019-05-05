#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"
#include "JFVKResource.h"

namespace JFFramework
{
    class JFVKVertexBuffer
    {
    public:
        JFVKVertexBuffer(JFVKDevice* device, size_t size);
        ~JFVKVertexBuffer();

    private:
        JFObject<JFVKResource> buffer;

        JFObject<JFVKDevice> device;
    };
}