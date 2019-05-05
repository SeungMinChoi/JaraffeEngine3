#include "JFVKVertexBufer.h"

JFFramework::JFVKVertexBuffer::JFVKVertexBuffer(JFVKDevice* _device, JFArray<byte*> vertexData, uint32_t dataStride)
    : device(_device)
{
    buffer = new JFVKResource(device, 
                              VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                              VK_SHARING_MODE_EXCLUSIVE,
							  vertexData);

	// VkVertexInputBinding 
	inputDescription.binding = 0;
	inputDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	inputDescription.stride = dataStride;
	
	// VkVertexInputAttribute ( 구조체, 데이터 해석에 도움을 주는 정보를 저장 -> vertexData들.. position 이런거 )
	inputAttributeDescription[0].binding = 0;
	inputAttributeDescription[0].location = 0;
	inputAttributeDescription[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	inputAttributeDescription[0].offset = 0;

	inputAttributeDescription[1].binding = 0;
	inputAttributeDescription[1].location = 1;
	inputAttributeDescription[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	inputAttributeDescription[1].offset = 16;
}

JFFramework::JFVKVertexBuffer::~JFVKVertexBuffer()
{
}
