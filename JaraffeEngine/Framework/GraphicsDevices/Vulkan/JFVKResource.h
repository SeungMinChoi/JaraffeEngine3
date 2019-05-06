#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"

namespace JFFramework
{
	// 순서
	// 1) 버퍼 생성
	// 2) 버퍼 메모리 요구사항
	// 3) 메모리 유형 결정
	// 4) 메모리 할당
	// 5) 스테이지
	// 6) 메모리 바인딩
	// 7) 버퍼 뷰 생성
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