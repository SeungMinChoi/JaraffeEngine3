#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JF_API JFSize
	{
	public:
		static const JFSize Zero;

		JFSize();
		JFSize(float s);
		JFSize(float width, float height);

		float width;
		float height;
	};
}