#pragma once

#include "JFVKInclude.h"
#include "../../../JFFoundation.h"

#include "JFVKDevice.h"
#include "../../Platform/JFWindow.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFVKSurface
	{
	public:
		JFVKSurface(JFWindow* window, JFVKDevice* device);
		~JFVKSurface();

		void Create();
		void Destroy();

		VkSurfaceKHR surface;

	private:
		JFObject<JFWindow> window;
		JFObject<JFVKDevice> device;
	};
}