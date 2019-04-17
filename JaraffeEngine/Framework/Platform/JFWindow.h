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

		void* Handle() const;

	private:
		void* impl;
	};
}