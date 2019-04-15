#pragma once

#include "../../../JFFoundation.h"
#include "JFVulkanInclude.h"

namespace Framework
{
	// Windows �������� �Ʒ� ������Ʈ������ Layer����� ������ (json ������)
	//HKEY_LOCAL_MACHINE\SOFTWARE\Khronos\Vulkan\ExplicitLayers
	//HKEY_LOCAL_MACHINE\SOFTWARE\Khronos\Vulkan\ImplicitLayers

	// Layer �˻�� ���� �ܰ迡�� ����ϰ� ���������� �����ؼ� ��ȿ�� �˻� ����� ���ϼ� ����
	// TODO : ���� �ϴ� ����... ���� ���̵�� �������� ���ľ���. 
	// -> ���� ����̽����� �����ϴ� layer, extentsion����Ʈ�� �ӳ����� �װ� �����ؼ� �� �� �ְ��ϴ� ���� ������ ������. �װ� �����س���
	class JFVulkanLayerChecker
	{
	public:
		static bool CheckLayer(JFFoundation::JFArray<const char*> layers);

		// Ȯ���ǿ��� 2���� ������ �ֽ��ϴ�.
		// 1. �ν��Ͻ� ��� : � ��ġ�͵� �������� ���� ������� � VkDevice ���̵� �׼��� ����.
		// 2. ��ġ ��� : �� Ȯ������ ��ġ�� Ư���� ������ �־� Ư�� ����� �����ϰ� ���� ���α׷��� �����Ϸ��� ��ġ�� ��ȿ�� �ڵ��� �ʿ�.
		static bool CheckInstanceExtension(JFFoundation::JFArray<const char*> extensions);
		static bool CheckDeviceExtension(VkPhysicalDevice* device, JFFoundation::JFArray<const char*> extensions);
	private:
		static const JFFoundation::JFArray<VkLayerProperties>& LayerProperties();
	};
}