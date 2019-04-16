#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JF_API JFVector4
	{
	public:
		static const JFVector4 One;
		static const JFVector4 Zero;

		JFVector4();
		JFVector4(float s);
		JFVector4(float x, float y, float z, float w);

		JFVector4 operator * (float s) const;
		JFVector4 operator / (float s) const;

		JFVector4& operator *= (float s);
		JFVector4& operator /= (float s);

		JFVector4 operator + (const JFVector4& v) const;
		JFVector4 operator - (const JFVector4& v) const;
		JFVector4 operator * (const JFVector4& v) const;
		JFVector4 operator / (const JFVector4& v) const;

		JFVector4& operator += (const JFVector4& v);
		JFVector4& operator -= (const JFVector4& v);
		JFVector4& operator *= (const JFVector4& v);
		JFVector4& operator /= (const JFVector4& v);

		float Dot(const JFVector4& v) const;
		static float Dot(const JFVector4& v1, const JFVector4& v2);

		float Length() const;
		float LengthSqrt() const;

		JFVector4& Normalize();

	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float v[4];
		};
	};
}