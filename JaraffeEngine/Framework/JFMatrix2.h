#pragma once

#include "../JFInclude.h"

namespace JFFramework
{
	class JF_API JFMatrix2
	{
	public:
		static const JFMatrix2 Identity;

		JFMatrix2();
		JFMatrix2(float s);
		JFMatrix2(float _11, float _12,
				  float _21, float _22);

		JFMatrix2 operator * (const JFMatrix2& m) const;
		JFMatrix2 operator + (const JFMatrix2& m) const;
		JFMatrix2 operator - (const JFMatrix2& m) const;

		JFMatrix2 operator *= (const JFMatrix2& m) const;
		JFMatrix2 operator += (const JFMatrix2& m) const;
		JFMatrix2 operator -= (const JFMatrix2& m) const;

	public:
		union
		{
			struct
			{
				float _11, _12;
				float _21, _22;
			};
			float m[2][2];
		};
	};
}