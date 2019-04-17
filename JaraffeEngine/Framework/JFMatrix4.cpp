#include "JFMatrix4.h"

using namespace JFFramework;

const JFMatrix4 JFFramework::JFMatrix4::Identity = JFMatrix4();

JFFramework::JFMatrix4::JFMatrix4()
	: _11(1), _12(0), _13(0), _14(0)
	, _21(0), _22(1), _23(0), _24(0)
	, _31(0), _32(0), _33(1), _34(0)
	, _41(0), _42(0), _43(0), _44(1)
{}

JFFramework::JFMatrix4::JFMatrix4(float s)
	: _11(s), _12(s), _13(s), _14(s)
	, _21(s), _22(s), _23(s), _24(s)
	, _31(s), _32(s), _33(s), _34(s)
	, _41(s), _42(s), _43(s), _44(s)
{}

JFFramework::JFMatrix4::JFMatrix4(float __11, float __12, float __13, float __14,
								  float __21, float __22, float __23, float __24,
								  float __31, float __32, float __33, float __34,
								  float __41, float __42, float __43, float __44)
	: _11(__11), _12(__12), _13(__13), _14(__14)
	, _21(__21), _22(__22), _23(__23), _24(__24)
	, _31(__31), _32(__32), _33(__33), _34(__34)
	, _41(__41), _42(__42), _43(__43), _44(__44)
{}

JFMatrix4 JFFramework::JFMatrix4::operator*(const JFMatrix4& m) const
{
	return JFMatrix4();
}

JFMatrix4 JFFramework::JFMatrix4::operator+(const JFMatrix4& m) const
{
	return JFMatrix4();
}

JFMatrix4 JFFramework::JFMatrix4::operator-(const JFMatrix4& m) const
{
	return JFMatrix4();
}

JFMatrix4 JFFramework::JFMatrix4::operator*=(const JFMatrix4& m) const
{
	return JFMatrix4();
}

JFMatrix4 JFFramework::JFMatrix4::operator+=(const JFMatrix4& m) const
{
	return JFMatrix4();
}

JFMatrix4 JFFramework::JFMatrix4::operator-=(const JFMatrix4& m) const
{
	return JFMatrix4();
}
