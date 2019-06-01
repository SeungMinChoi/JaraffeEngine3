#pragma once

#include "../JFInclude.h"
#include "../JFFoundation.h"
#include "Platform/JFWindow.h"
#include "GraphicsDevices/JFGraphicsDevice.h"

using namespace JFFoundation;

namespace JFFramework
{
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

		void SetupConsole();
		void DestroyConsole();

	private:
		bool isExit = false;

		JFWindow* window;
		JFGraphicsDevice* graphicsDevice;
	};
}