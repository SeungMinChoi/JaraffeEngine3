#pragma once

#include "../../../JFFoundation.h"

#include "JFVKInclude.h"
#include "JFVKDevice.h"
#include "JFVKSwapChain.h"

namespace JFFramework
{
    class JFVKRenderPass
    {
    public:
        JFVKRenderPass(JFVKDevice* device, JFVKSwapChain* swapChain);
        ~JFVKRenderPass() noexcept;

    private:
        void CreateRenderPass();

    private:
        VkRenderPass renderPass;

        JFObject<JFVKDevice> device;
        JFObject<JFVKSwapChain> swapChain;
    };
}