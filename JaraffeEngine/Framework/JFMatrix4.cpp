#include "JFMatrix3.h"

using namespace JFFramework;

const JFMatrix3 JFFramework::JFMatrix3::Identity = JFMatrix3();

JFFramework::JFMatrix3::JFMatrix3()
	: _11(1), _12(0), _13(0)
	, _21(0), _22(1), _23(0)
	, _31(0), _32(0), _33(1)
{
}

JFFramework::JFMatrix3::JFMatrix3(float s)
	: _11(s), _12(s), _13(s)
	, _21(s), _22(s), _23(s)
	, _31(s), _32(s), _33(s)
{
}

JFFramework::JFMatrix3::JFMatrix3(float __11, float __12, float __13,
								  float __21, float __22, float __23,
								  float __31, float __32, float __33)
	: _11(__11), _12(__12), _13(__13)
	, _21(__21), _22(__22), _23(__23)
	, _31(__31), _32(__32), _33(__33)
{
}

JFMatrix3 JFFramework::JFMatrix3::operator*(const JFMatrix3& m) const
{
	return JFMatrix3();
}

JFMatrix3 JFFramework::JFMatrix3::operator+(const JFMatrix3& m) const
{
	return JFMatrix3();
}

JFMatrix3 JFFramework::JFMatrix3::operator-(const JFMatrix3& m) const
{
	return JFMatrix3();
}

JFMatrix3 JFFramework::JFMatrix3::operator*=(const JFMatrix3& m) const
{
	return JFMatrix3();
}

JFMatrix3 JFFramework::JFMatrix3::operator+=(const JFMatrix3& m) const
{
	return JFMatrix3();
}

JFMatrix3 JFFramework::JFMatrix3::operator-=(const JFMatrix3& m) const
{
	return JFMatrix3();
}
