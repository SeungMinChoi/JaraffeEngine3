#include "JFVulkanCommandBuffer.h"
#include "JFVulkanDevice.h"
#include "JFVulkanTools.h"

JFFramework::JFCommandBuffer::JFCommandBuffer(JFVulkanDevice* _device)
	: device(_device)
{
	// commandpool 생성.
	VkCommandPoolCreateInfo cmdPoolInfo = {};
	cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmdPoolInfo.pNext = nullptr;

	// VK_COMMAND_POOL_CREATE_TRANSIENT_BIT 
	// -> 이 풀에서 할당된 커맨드 버퍼가 자주 변경되고 수명이 짧음을 나타냄. ( 짧은 시간 내에 버퍼가 리셋되거나 해제되는상황 )
	// VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT 
	// -> 이 풀에서 할당된 커맨드 버퍼가 두 가지 방법으로 개별적으로 리셋가능. ( 이 플레그를 사용 안할시 아래 두 API사용하면 안됨. vkResetCommandPool로만 전체 리셋 가능. )
	//    - 명시적 : vkResetCommandBuffer
	//    - 암묵적 : vkBeginCommandBuffer
	cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	
	// 커맨드 버퍼가 제출될 큐 패밀리 지정 ( 일단 임시값 )
	cmdPoolInfo.queueFamilyIndex = 0;

	VK_CHECK_RESULT(vkCreateCommandPool(device->device, &cmdPoolInfo, nullptr, &cmdPool));
}

JFFramework::JFCommandBuffer::~JFCommandBuffer()
{
	vkDestroyCommandPool(device->device, cmdPool, nullptr);
}

void JFFramework::JFCommandBuffer::Alloc()
{
	// CommandPool로 부터 CommandBuffer할당 ( 일단 이렇게 )
	VkCommandBufferAllocateInfo cmdInfo = {};
	cmdInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdInfo.pNext = nullptr;
	cmdInfo.commandPool = cmdPool;
	cmdInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmdInfo.commandBufferCount = buffers.Count();

	VK_CHECK_RESULT(vkAllocateCommandBuffers(device->device, &cmdInfo, buffers.Data()));
}

void JFFramework::JFCommandBuffer::Begin()
{
	VkCommandBufferInheritanceInfo cmdBufInheritInfo = {};
	cmdBufInheritInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	cmdBufInheritInfo.pNext = NULL;
	cmdBufInheritInfo.renderPass = VK_NULL_HANDLE;
	cmdBufInheritInfo.subpass = 0;
	cmdBufInheritInfo.framebuffer = VK_NULL_HANDLE;
	cmdBufInheritInfo.occlusionQueryEnable = VK_FALSE;
	cmdBufInheritInfo.queryFlags = 0;
	cmdBufInheritInfo.pipelineStatistics = 0;

	VkCommandBufferBeginInfo cmdBufInfo = {};
	cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBufInfo.pNext = NULL;
	cmdBufInfo.flags = 0;
	cmdBufInfo.pInheritanceInfo = &cmdBufInheritInfo;

	for (auto cmdbuf : buffers)
	{
		VK_CHECK_RESULT(vkBeginCommandBuffer(cmdbuf, &cmdBufInfo));
	}
}

void JFFramework::JFCommandBuffer::End()
{
	for (auto cmdbuf : buffers)
	{
		VK_CHECK_RESULT(vkEndCommandBuffer(cmdbuf));
	}
}

void JFFramework::JFCommandBuffer::Submit(const VkQueue& queue, const VkFence& fence)
{
	// Otherwise, create the submit information with specified buffer commands
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = NULL;
	submitInfo.waitSemaphoreCount = 0;
	submitInfo.pWaitSemaphores = NULL;
	submitInfo.pWaitDstStageMask = NULL;
	submitInfo.commandBufferCount = buffers.Count;
	submitInfo.pCommandBuffers = buffers.Data();
	submitInfo.signalSemaphoreCount = 0;
	submitInfo.pSignalSemaphores = NULL;

	// queue에 제출.
	VK_CHECK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, fence));

	// 완료 될때까지 기다림.
	VK_CHECK_RESULT(vkQueueWaitIdle(queue));
}

void JFFramework::JFCommandBuffer::Reset()
{
	vkResetCommandPool(device->device, cmdPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);

	//for (auto cmdbuf : buffers)
	//{
	//	// VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT = 커맨드 버퍼가 보유한 메모리가 커맨드 풀로 반환된다는 뜻.
	//	VK_CHECK_RESULT(vkResetCommandBuffer(cmdbuf, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT));
	//}
	buffers.Clear();
}

void JFFramework::JFCommandBuffer::Free()
{
	vkFreeCommandBuffers(device->device, cmdPool, buffers.Count(), buffers.Data());
	buffers.Clear();
}
