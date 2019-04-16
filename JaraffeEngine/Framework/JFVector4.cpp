#include "JFVector4.h"
#include <math.h>

using namespace JFFramework;

const JFVector4 JFFramework::JFVector4::One = JFVector4(1);
const JFVector4 JFFramework::JFVector4::Zero = JFVector4(0);

JFFramework::JFVector4::JFVector4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{}

JFFramework::JFVector4::JFVector4(float s)
	: x(s), y(s), z(s), w(s)
{}

JFFramework::JFVector4::JFVector4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{}

JFVector4 JFFramework::JFVector4::operator*(float s) const
{
	return JFVector4(x * s, y * s, z * s, w * s);
}

JFVector4 JFFramework::JFVector4::operator/(float s) const
{
	return JFVector4(x / s, y / s, z / s, w / s);
}

JFVector4& JFFramework::JFVector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

JFVector4& JFFramework::JFVector4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

JFVector4 JFFramework::JFVector4::operator+(const JFVector4& v) const
{
	return JFVector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

JFVector4 JFFramework::JFVector4::operator-(const JFVector4& v) const
{
	return JFVector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

JFVector4 JFFramework::JFVector4::operator*(const JFVector4& v) const
{
	return JFVector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

JFVector4 JFFramework::JFVector4::operator/(const JFVector4& v) const
{
	return JFVector4(x / v.x, y / v.y, z / v.z, w / v.w);
}

JFVector4& JFFramework::JFVector4::operator+=(const JFVector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

JFVector4& JFFramework::JFVector4::operator-=(const JFVector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

JFVector4& JFFramework::JFVector4::operator*=(const JFVector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

JFVector4& JFFramework::JFVector4::operator/=(const JFVector4& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

float JFFramework::JFVector4::Dot(const JFVector4& v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

float JFFramework::JFVector4::Dot(const JFVector4& v1, const JFVector4& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

float JFFramework::JFVector4::Length() const
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

float JFFramework::JFVector4::LengthSqrt() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

JFVector4& JFFramework::JFVector4::Normalize()
{
	float lengthSqrt = (x * x) + (y * y) + (z * z) + (w * w);
	if (lengthSqrt > 0.0f)
	{
		float lengthInv = 1.0f / sqrtf(lengthSqrt);
		x *= lengthInv;
		y *= lengthInv;
		z *= lengthInv;
		w *= lengthInv;
	}

	return *this;
}
