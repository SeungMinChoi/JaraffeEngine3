#include "JFVKCommandBuffer.h"
#include "JFVKTools.h"

JFFramework::JFVKCommandBuffer::JFVKCommandBuffer(JFVKDevice* _device)
	: device(_device)
	, commandPool(VK_NULL_HANDLE)
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
	cmdPoolInfo.queueFamilyIndex = device->graphicsQueueIndex;

	VK_CHECK_RESULT(vkCreateCommandPool(device->device, &cmdPoolInfo, nullptr, &commandPool));
}

JFFramework::JFVKCommandBuffer::~JFVKCommandBuffer()
{
	if(buffers.Count())
		vkFreeCommandBuffers(device->device, commandPool, (uint32_t)buffers.Count(), buffers.Data());

	if(commandPool != VK_NULL_HANDLE)
		vkDestroyCommandPool(device->device, commandPool, nullptr);
}

JFArray<VkCommandBuffer>& JFFramework::JFVKCommandBuffer::Begin(size_t count)
{
	// 할당 요청한 개수를 초과해서 가지고 있다면 pool에 반환합니다.
	for (size_t i = buffers.Count(); i < (count-1); ++i)
	{
		// VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT = 커맨드 버퍼가 보유한 메모리가 커맨드 풀로 반환된다는 뜻.
		VK_CHECK_RESULT(vkResetCommandBuffer(buffers[i], VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT));
	}
	buffers.Resize(count);

	// CommandPool로 부터 CommandBuffer할당 ( 일단 이렇게 )
	VkCommandBufferAllocateInfo cmdInfo = {};
	cmdInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdInfo.pNext = nullptr;
	cmdInfo.commandPool = commandPool;
	cmdInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmdInfo.commandBufferCount = (uint32_t)count;

	VK_CHECK_RESULT(vkAllocateCommandBuffers(device->device, &cmdInfo, buffers.Data()));

	// Begin
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

	for (auto buf : buffers)
	{
		VK_CHECK_RESULT(vkBeginCommandBuffer(buf, &cmdBufInfo));
	}

	return buffers;
}

void JFFramework::JFVKCommandBuffer::End()
{
	for (auto buf : buffers)
	{
		VK_CHECK_RESULT(vkEndCommandBuffer(buf));
	}
}

void JFFramework::JFVKCommandBuffer::Submit(const VkFence& fence)
{
	// Otherwise, create the submit information with specified buffer commands
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = NULL;
	submitInfo.waitSemaphoreCount = 0;
	submitInfo.pWaitSemaphores = NULL;
	submitInfo.pWaitDstStageMask = NULL;
	submitInfo.commandBufferCount = (uint32_t)buffers.Count();
	submitInfo.pCommandBuffers = buffers.Data();
	submitInfo.signalSemaphoreCount = 0;
	submitInfo.pSignalSemaphores = NULL;

	// queue에 제출.
	VK_CHECK_RESULT(vkQueueSubmit(device->queue, 1, &submitInfo, fence));

	// 완료 될때까지 기다림.
	VK_CHECK_RESULT(vkQueueWaitIdle(device->queue));
}

//JFVKCommandBuffer& JFFramework::JFVKCommandBuffer::operator=(JFVKCommandBuffer && r)
//{
//	buffers = r.buffers;
//	commandPool = r.commandPool;
//	r.commandPool = nullptr;
//
//	JFArray<VkCommandBuffer> buffers;
//	// TODO: 여기에 반환 구문을 삽입합니다.
//}
