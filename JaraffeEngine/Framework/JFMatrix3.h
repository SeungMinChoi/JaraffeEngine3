#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JF_API JFMatrix3
	{
	public:
		static const JFMatrix3 Identity;

		JFMatrix3();
		JFMatrix3(float s);
		JFMatrix3(float _11, float _12, float _13,
				  float _21, float _22, float _23,
				  float _31, float _32, float _33);

		JFMatrix3 operator * (const JFMatrix3& m) const;
		JFMatrix3 operator + (const JFMatrix3& m) const;
		JFMatrix3 operator - (const JFMatrix3& m) const;

		JFMatrix3 operator *= (const JFMatrix3& m) const;
		JFMatrix3 operator += (const JFMatrix3& m) const;
		JFMatrix3 operator -= (const JFMatrix3& m) const;

	public:
		union
		{
			struct
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float m[3][3];
		};
	};
}