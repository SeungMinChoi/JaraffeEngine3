#pragma once

#include "JFVKInclude.h"
#include "JFVKDevice.h"
#include "../../../JFFoundation.h"

using namespace JFFoundation;

namespace JFFramework
{
	// Vulkan의 이미지는 연속된 텍스처 데이터를 1D/2D/3D 형식으로 표현. 기본적으로 첨부, 텍스처로 사용
	// 첨부(Attachment) : 이미지가 파이프라인에 첨부돼 색상 또는 깊이로 사용되거나 다중 패스 처리를 위한 보조 화면으로 사용 가능
	// 텍스처(Texture) : 이미지가 디스크립터처럼 사용되고 샘플러 형식으로 셰이더 스테이지에 공유된다.

	// 텍스처 기본개념
	// 이미지 : 텍스처 개체, 메모리 요구량을 계산하는 데 사용하는 메타 데이터 포함(포맷, 크기, 유형등등..)
	// 이미지 레이아웃 : 이미지 텍스처 정보를 이미지 메모리 그리드 좌표로 저장하는 방법. 저장되는 방법은 Vulkan구현마다 다름.
	//					 각 이미지는 색상 첨부, 셰이더의 샘플 이미지, 이미지 로드/저장 또는 큰 이미지를 위한 희소 텍스처와 같은 특정 용도를 갖고 있다.
	//					 이러한 특별 목적을 위해 최적의 성능을 제공하는 이미지 메모리 용도에 특화.
	// 이미지 뷰 : 이미지는 API호출, 파이프라인 셰이더가 직접 읽기와 쓰기 목적으로 사용할 수 없다. 그럴때 사용되는게 이미지 뷰.
	//             이미지 뷰는 이미지 개체에 대한 인터페이스처럼 작동할 뿐만 아니라 이미지 하위 리소스의 범위를 나타내는 데 사용하는 메타 데이터도 제공.

	// 간단한 이미지 생성 과정
	// 1. 이미지 개체 생성( vkCreateImage )
	// 2. 이미지 메모리 할당
	//		- 메모리 요구사항 얻기
	//		- 메모리 유형 결정
	//		- 장치 메모리 할당
	//		- 할당된 메모리 바인딩
	// 3. 이미지 레이아웃 설정
	// 4. 이미지 뷰 생성. ( 이미지는 이미지 뷰를 통해서만 액세스 가능 )
	class JFVKImage
	{
	public:
		JFVKImage(JFVKDevice* device);
		~JFVKImage();

	private:
		void SetImageLayer(VkImage image, 
						   VkImageAspectFlags aspectMask, 
						   VkImageLayout oldImageLayout, 
						   VkImageLayout newImageLayout, 
						   VkAccessFlagBits srcAccessMask, 
						   const VkCommandBuffer& cmd);

		VkImage image;
		VkImageView	view;
		VkDeviceMemory memory;

		JFObject<JFVKDevice> device;
	};
}