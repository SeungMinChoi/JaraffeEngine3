#pragma once

#include "JFVKInclude.h"
#include "../../../JFFoundation.h"

#include "JFVKDevice.h"

using namespace JFFoundation;

namespace JFFramework
{
	// 1차 커맨드 버퍼 : 2차 커맨드 버퍼의 소유자로, 이들을 실행하는 책임이 있고 큐에 직접 제출한다.
	// 2차 커맨드 버퍼 : 1차 커맨드 버퍼를 통해 실행되며 큐에 직접 제출할 수 있다.
	// 커맨드 버퍼는 커맨드 풀에서 할당됨 -> 이를통해서 다중 커맨드 버퍼에서 리소스를 생성하는 비용 최소화.
	// 한번 만들어지면 계속 재사용 가능.
	// 다중스레드에서는 버퍼간의 동기화 관리 필요.
	// 커맨드 버퍼는 비동기적으로 처리되는 하드웨어 큐에 제출( 제출시에는 배치를 만들고 한번에 실행하면 효율적 )

	// 커맨드 종류
	// - 동작 : 그리기, 전송(dispatch), 지우기, 복사, 쿼리, 타임스탬프 작업, 서브패스의 시작과 종료
	// - 스테이트 관리 : 디스크립터 세트, 파이프라인 바인딩, 버퍼를 포함하며, 동적 스테이트, 상수의 푸시, 렌더 패스와 서브패스 스테이트를 설정하는 데 사용.
	// - 동기화 : 동기화에 사용, 파이프라인 장벽, 이벤트 설정, 대기 이벤트, 렌더 패스와 서브패스의 종속성 등이 포함

	// 제출 방식
	// - 단일 큐 : 여러 개의 커맨드 버퍼는 실행되거나 중첩가능. 각명령의 순서와 표준에서 정의된 API실행 순서에 따라 수행돼야 한다.
	// - 복수 큐 : 특별한 순서 없이 실행된다. 순서 지정은 세마포어 나 펜스를 통한 동기화를 통해서만 가능하다.
	class JFVKCommandBuffer
	{
	public:
		JFVKCommandBuffer(JFVKDevice* device);
		~JFVKCommandBuffer();

		// Begine과 End사이의 명령들을 레코딩, Submit으로 제출.
		JFArray<VkCommandBuffer>& Begin(size_t count);
		void End();
		void Submit(const VkFence& fence = VK_NULL_HANDLE);

	private:
		JFObject<JFVKDevice> device;

		VkCommandPool commandPool;
		JFArray<VkCommandBuffer> buffers;
	};
}