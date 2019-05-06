#pragma once

#include "JFVKInclude.h"

namespace JFFramework
{
	// Vulkan은 메모리를 크게 2가지로 구분
	// 1. 호스트 메모리 : 장치 메모리 보다는 속도가 느리지만 메모리 크기가 훨씬 큼.
	// 2. 장치 메모리 : 물리적 장치에 직접 접근 가능하므로 효율성이 높고 속도가 빠름.

	// 호스트 메모리
	// Vulkan은 내부에서 사용하는 API데이터 구조체를 저장하기 위해 호스트 메모리를 사용.
	// 응용 프로그램이 할당 함수를 제공하면 호스트 메모리 할당에 사용.
	// 제공하지 않는다면 디폴트 할당 스킴(scheme)을 사용.
	// https://www.khronos.org/registry/vulkan/specs/1.0/apispec.html 참조.
	//VkAllocationCallBacks

	// 장치 메모리
	// GPU메모리
	// 이미지 개체, 버퍼 개체, 유니폼 버퍼 개체는 모두 장치 메모리에서 할당.
	// 하나의 물리적 장치에 여러 종류의 메모리가 존재할 수 있으며, 힙과 속성에 따라 추가적으로 세분된다.
	// vkGetPhysicalDeviceMemoryProperties()는 물리적 장치에서 사용가능한 메모리 힙과 메모리 속성을 쿼리.
	// vkAllocateMemory 를 통해 장치메모리 할당 가능.
	// 당연히 해제는 vkFreeMemory()

	class JFVKDevice;
	namespace JFVKMemory
	{
		bool MemoryTypeFromProperties(JFVKDevice* device, uint32_t typeBits, VkFlags requirementsMask, uint32_t* typeIndex);
	}
}