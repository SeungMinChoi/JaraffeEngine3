#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JF_API JFVector2
	{
	public:
		static const JFVector2 One;
		static const JFVector2 Zero;

		JFVector2();
		JFVector2(float s);
		JFVector2(float x, float y);

		JFVector2 operator * (float s) const;
		JFVector2 operator / (float s) const;

		JFVector2& operator *= (float s);
		JFVector2& operator /= (float s);

		JFVector2 operator + (const JFVector2& v) const;
		JFVector2 operator - (const JFVector2& v) const;
		JFVector2 operator * (const JFVector2& v) const;
		JFVector2 operator / (const JFVector2& v) const;

		JFVector2& operator += (const JFVector2& v);
		JFVector2& operator -= (const JFVector2& v);
		JFVector2& operator *= (const JFVector2& v);
		JFVector2& operator /= (const JFVector2& v);

		float Dot(const JFVector2& v) const;
		static float Dot(const JFVector2& v1, const JFVector2& v2);

		float Length() const;
		float LengthSqrt() const;

		JFVector2& Normalize();

	public:
		union
		{
			struct
			{
				float x;
				float y;
			};
			float v[2];
		};
	};
}