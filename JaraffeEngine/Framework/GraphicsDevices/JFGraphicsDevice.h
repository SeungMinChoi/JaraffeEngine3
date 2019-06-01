#pragma once

#include "../../JFInclude.h"

namespace JFFramework
{
	class JFWindow;
	class JFGraphicsDevice
	{
	public:
		JFGraphicsDevice();
		~JFGraphicsDevice();

		void Create(JFWindow* window);
		void Destroy();

		void Render();

	private:
		void* impl;
	};
}