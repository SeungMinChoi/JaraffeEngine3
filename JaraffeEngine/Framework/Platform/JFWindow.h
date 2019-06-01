#pragma once

#include "../JFSize.h"
#include "../../JFInclude.h"

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

		JFSize size;

	private:
		void* impl;
	};
}