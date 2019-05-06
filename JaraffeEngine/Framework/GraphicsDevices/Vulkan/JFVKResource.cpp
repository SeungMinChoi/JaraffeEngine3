#include "JFVKResource.h"
#include "JFVKMemory.h"
#include "JFVKTools.h"
#include "JFVKRenderPass.h"

JFFramework::JFVKResource::JFVKResource(JFVKDevice* _device, 
                                        VkBufferUsageFlagBits usage, 
                                        VkSharingMode mode, 
										JFArray<byte*> data)
    : device(_device)
{
	// 1) Create Buffer
    VkBufferCreateInfo bufferCreateInfo = {};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.pNext = nullptr;
    bufferCreateInfo.usage = usage;
    bufferCreateInfo.size = data.Count();
    bufferCreateInfo.queueFamilyIndexCount = 0;
    bufferCreateInfo.pQueueFamilyIndices = nullptr;
    bufferCreateInfo.sharingMode = mode;
    bufferCreateInfo.flags = 0;

    VK_CHECK_RESULT(vkCreateBuffer(device->device, &bufferCreateInfo, nullptr, &buffer));

	// 2) Alloc Memory
	// 리소스 요구사항
	VkMemoryRequirements memRqrmnt;
	vkGetBufferMemoryRequirements(device->device, buffer, &memRqrmnt);

	// 메모리 할당 메타 데이터 정보 생성
	VkMemoryAllocateInfo allocInfo;
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.memoryTypeIndex = 0;
	allocInfo.allocationSize = memRqrmnt.size;

	// 호환되는 메모리 유형을 가져오기
	JFVKMemory::MemoryTypeFromProperties(device,
							 memRqrmnt.memoryTypeBits,
							 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
							 VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
							 &allocInfo.memoryTypeIndex);

	// 버퍼 리소스를 위한 물리적 저장 공간 할당
	VK_CHECK_RESULT(vkAllocateMemory(device->device, &allocInfo, nullptr, &memory));

	bufferInfo.range = memRqrmnt.size;
	bufferInfo.offset = 0;

	// 호스트에 물리적 장치 메모리 공간을 매핑
	void* mappingMemoryData;
	VK_CHECK_RESULT(vkMapMemory(device->device, memory, 0, memRqrmnt.size, 0, &mappingMemoryData));

	// 데이터를 매핑된 메모리에 복사
	memcpy_s(mappingMemoryData, memRqrmnt.size, data.Data(), data.Count());

	// 장치 메모리를 매핑 해제
	vkUnmapMemory(device->device, memory);

	// 할당된 버퍼 리소스를 장치 메모리에 바인딩
	VK_CHECK_RESULT(vkBindBufferMemory(device->device, buffer, memory, 0));
}

JFFramework::JFVKResource::~JFVKResource() noexcept
{
    vkDestroyBuffer(device->device, buffer, nullptr);
	vkFreeMemory(device->device, memory, nullptr);
}
