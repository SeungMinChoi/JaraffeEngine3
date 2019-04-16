#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JF_API JFVector3
	{
	public:
		static const JFVector3 One;
		static const JFVector3 Zero;

		JFVector3();
		JFVector3(float s);
		JFVector3(float x, float y, float z);

		JFVector3 operator * (float s) const;
		JFVector3 operator / (float s) const;

		JFVector3& operator *= (float s);
		JFVector3& operator /= (float s);

		JFVector3 operator + (const JFVector3& v) const;
		JFVector3 operator - (const JFVector3& v) const;
		JFVector3 operator * (const JFVector3& v) const;
		JFVector3 operator / (const JFVector3& v) const;

		JFVector3& operator += (const JFVector3& v);
		JFVector3& operator -= (const JFVector3& v);
		JFVector3& operator *= (const JFVector3& v);
		JFVector3& operator /= (const JFVector3& v);

		float Dot(const JFVector3& v) const;
		static float Dot(const JFVector3& v1, const JFVector3& v2);

		JFVector3 Cross(const JFVector3& v) const;
		static JFVector3 Cross(const JFVector3& v1, const JFVector3& v2);

		float Length() const;
		float LengthSqrt() const;

		JFVector3& Normalize();

	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float v[3];
		};
	};
}