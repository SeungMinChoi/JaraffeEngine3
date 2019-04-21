#pragma once

#include "JFVKInclude.h"
#include "../../../JFFoundation.h"

using namespace JFFoundation;

namespace JFFramework
{
	class JFWindow;
	class JFVKDevice;
	class JFVKSurface
	{
	public:
		JFVKSurface(JFWindow* window, JFVKDevice* device);
		~JFVKSurface();

		void Create();
		void Destroy();

	private:
		VkSurfaceKHR surface;

		JFObject<JFWindow> window;
		JFObject<JFVKDevice> device;
	};
}