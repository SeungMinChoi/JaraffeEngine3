#include "JFVector2.h"
#include <math.h>

using namespace JFFramework;

const JFVector2 JFFramework::JFVector2::One = JFVector2(1);
const JFVector2 JFFramework::JFVector2::Zero = JFVector2(0);

JFFramework::JFVector2::JFVector2()
	: x(0.0f), y(0.0f)
{}

JFFramework::JFVector2::JFVector2(float s)
	: x(s), y(s)
{}

JFFramework::JFVector2::JFVector2(float _x, float _y)
	: x(_x), y(_y)
{}

JFVector2 JFFramework::JFVector2::operator*(float s) const
{
	return JFVector2(x * s, y * s);
}

JFVector2 JFFramework::JFVector2::operator/(float s) const
{
	return JFVector2(x / s, y / s);
}

JFVector2& JFFramework::JFVector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

JFVector2& JFFramework::JFVector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

JFVector2 JFFramework::JFVector2::operator+(const JFVector2& v) const
{
	return JFVector2(x + v.x, y + v.x);
}

JFVector2 JFFramework::JFVector2::operator-(const JFVector2& v) const
{
	return JFVector2(x - v.x, y - v.y);
}

JFVector2 JFFramework::JFVector2::operator*(const JFVector2& v) const
{
	return JFVector2(x * v.x, y + v.y);
}

JFVector2 JFFramework::JFVector2::operator/(const JFVector2& v) const
{
	return JFVector2(x / v.x, y / v.y);
}

JFVector2& JFFramework::JFVector2::operator+=(const JFVector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

JFVector2& JFFramework::JFVector2::operator-=(const JFVector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

JFVector2& JFFramework::JFVector2::operator*=(const JFVector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

JFVector2& JFFramework::JFVector2::operator/=(const JFVector2& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

float JFFramework::JFVector2::Dot(const JFVector2& v) const
{
	return (x * v.x) + (x * v.y);
}

float JFFramework::JFVector2::Dot(const JFVector2& v1, const JFVector2& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float JFFramework::JFVector2::Length() const
{
	return sqrtf((x * x) + (y * y));
}

float JFFramework::JFVector2::LengthSqrt() const
{
	return (x * x) + (y * y);
}

JFVector2& JFFramework::JFVector2::Normalize()
{
	float lengthSqrt = (x * x) + (y * y);
	if (lengthSqrt > 0.0f)
	{
		float lengthInv = 1.0f / sqrtf(lengthSqrt);
		x *= lengthInv;
		y *= lengthInv;
	}

	return *this;
}
