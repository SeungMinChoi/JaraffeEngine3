#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JF_API JFMatrix4
	{
	public:
		static const JFMatrix4 Identity;

		JFMatrix4();
		JFMatrix4(float s);
		JFMatrix4(float _11, float _12, float _13, float _14,
				  float _21, float _22, float _23, float _24,
				  float _31, float _32, float _33, float _34,
				  float _41, float _42, float _43, float _44);

		JFMatrix4 operator * (const JFMatrix4& m) const;
		JFMatrix4 operator + (const JFMatrix4& m) const;
		JFMatrix4 operator - (const JFMatrix4& m) const;

		JFMatrix4 operator *= (const JFMatrix4& m) const;
		JFMatrix4 operator += (const JFMatrix4& m) const;
		JFMatrix4 operator -= (const JFMatrix4& m) const;

	public:
		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};
	};
}