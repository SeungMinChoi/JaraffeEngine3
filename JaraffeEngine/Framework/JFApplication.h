#pragma once

#include "../JFInclude.h"
#include "../JFFoundation.h"

using namespace JFFoundation;

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

		void SetupConsole();
		void DestroyConsole();

		JFObject<JFWindow> window;
		JFObject<JFGraphicsDevice> graphicsDevice;
	};
}