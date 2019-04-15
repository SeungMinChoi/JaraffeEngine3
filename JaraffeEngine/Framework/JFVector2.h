#pragma once

namespace JFFramework
{
	class JFVector2
	{
	public:
		JFVector2();
		JFVector2(float x, float y);

		JFVector2 operator + (const JFVector2& v) const;
		JFVector2 operator - (const JFVector2& v) const;

		float x;
		float y;
	};
}