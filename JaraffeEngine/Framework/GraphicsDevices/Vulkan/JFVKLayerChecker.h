#pragma once

#include "../../../JFFoundation.h"
#include "JFVKInclude.h"

namespace Framework
{
	// Windows 기준으로 아래 레지스트리에서 Layer목록을 가져옴 (json 형태임)
	//HKEY_LOCAL_MACHINE\SOFTWARE\Khronos\Vulkan\ExplicitLayers
	//HKEY_LOCAL_MACHINE\SOFTWARE\Khronos\Vulkan\ImplicitLayers

	// Layer 검사는 개발 단계에서 사용하고 릴리지때는 제거해서 유효성 검사 비용을 줄일수 있음
	// TODO : 여기 일단 대충... 좋은 아이디어 생각나면 고쳐야함. 
	// -> 현재 디바이스들이 지원하는 layer, extentsion리스트가 쫙나오고 그걸 선택해서 고를 수 있게하는 툴이 있으면 좋을듯. 그거 저장해놓고
	class JFVKLayerChecker
	{
	public:
		static bool CheckLayer(JFFoundation::JFArray<const char*> layers);

		// 확장판에는 2가지 버전이 있습니다.
		// 1. 인스턴스 기반 : 어떤 장치와도 독립적인 전역 기능으로 어떤 VkDevice 없이도 액세스 가능.
		// 2. 장치 기반 : 이 확장판은 장치에 특별히 한정돼 있어 특수 기능을 조작하고 응용 프로그램에 제공하려면 장치에 유효한 핸들이 필요.
		static bool CheckInstanceExtension(JFFoundation::JFArray<const char*> extensions);
		static bool CheckDeviceExtension(VkPhysicalDevice* device, JFFoundation::JFArray<const char*> extensions);
	private:
		static const JFFoundation::JFArray<VkLayerProperties>& LayerProperties();
	};
}