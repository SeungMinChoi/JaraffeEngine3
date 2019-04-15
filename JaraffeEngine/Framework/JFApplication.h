#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JFWindow;
	class JFGraphicsDevice;
	class JF_API JFApplication
	{
	public:
		JFApplication();
		~JFApplication();

		void Run();

	private:
		void PreUpdate();
		void Update();
		void PostUpdate();

		void Render();

		void _SetupConsole();

		JFWindow* window;
		JFGraphicsDevice* graphicsDevice;
	};
}