#pragma once

namespace JFFramework
{
	class JFWindow
	{
	public:
		JFWindow();
		~JFWindow();

		void Create();
		void Destroy();

	private:
		void* impl;
	};
}