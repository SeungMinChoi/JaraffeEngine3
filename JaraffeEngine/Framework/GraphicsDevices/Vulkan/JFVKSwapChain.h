#pragma once

#include "JFVKInclude.h"

namespace JFFramework
{
	// 랜더링 결과를 플렛폼 지정 윈도 화면에 표시하는 기능
	// VK_KHR_SWAPCHAIN_EXTENSION_NAME 확장판 필요.

	// 드로잉 이미지의 교체 또는 플리핑(Flipping) 업데이트 주기는 아래 프레젠테이션 모드에 따라 달라집니다.
	// 수직동기화 주기(Vertical Blanking Interval - VBI) 에 맞춰서 업데이트 되는방식.
	// 드로잉 화면이 사용 가능한 즉시 업데이트 되는 방식이 있다.

	// 스왑 체인 구현 과정 ( 구현 완료후 삭제 예정 )
	// 1. 빈 윈도 생성
	// 2. 스왑 체인 확장판에 대한 쿼리
	// 3. 화면을 생성해 생성된 원도와 연결
	// 4. 지원되는 이미지 포맷 얻기
	// 5. 스왑 체인 이미지 화면 기능 쿼리
	// 6. 프레젠테이션 모드 정보 관리
	// 7. 스왑 체인 이미지 생성 및 프레젠테이션 이미지 검색
	// 8. 색상 이미지 뷰 생성
	// 9. 깊이 이미지 생성
	// 10. 깊이 이미지 메모리 할당
	// 11. 깊이 이미지 레이아웃 생성용 커맨드 풀 생성
	// 12. 커맨드 버퍼 작성
	// 13. 이미지 레이아웃 적용
	// 14. 파이프라인 장벽 추가
	// 15. 커맨드 버퍼 레코딩 종료
	// 16. 깊이 이미지 뷰 생성
	class JFVKDevice;
	class JFVKSurface;
	class JFVKSwapChain
	{
	public:
		JFVKSwapChain(JFVKDevice* device, JFVKSurface* surface);
		~JFVKSwapChain();

	private:
		VkSwapchainKHR swapChain;
	};
}