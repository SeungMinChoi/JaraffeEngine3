#include "JFVKMemory.h"
#include "JFVKDevice.h"

#include "JFVKTools.h"

bool JFFramework::JFVKMemory::MemoryTypeFromProperties(JFVKDevice* device, uint32_t typeBits, VkFlags requirementsMask, uint32_t* typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < 32; i++)
	{
		if ((typeBits & 1) == 1)
		{
			// Type is available, does it match user properties?
			if ((device->memoryProperties.memoryTypes[i].propertyFlags & requirementsMask) == requirementsMask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return false;
}