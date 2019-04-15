#pragma once

namespace JFFramework
{
	class JFGraphicsDeviceInterface;
	class JFGraphicsDevice
	{
	public:
		JFGraphicsDevice();
		~JFGraphicsDevice();

	private:
		JFGraphicsDeviceInterface* device;
	};
}