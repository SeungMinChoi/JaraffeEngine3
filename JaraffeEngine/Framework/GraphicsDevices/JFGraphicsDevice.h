#pragma once

namespace JFFramework
{
	class JFWindow;
	class JFSwapChainInterface;
	class JFGraphicsDeviceInterface;
	class JFGraphicsDevice
	{
	public:
		JFGraphicsDevice();
		~JFGraphicsDevice();

		void Create(JFWindow* window);
		void Destroy();

	private:
		JFSwapChainInterface* swapChain;
		JFGraphicsDeviceInterface* device;
	};
}