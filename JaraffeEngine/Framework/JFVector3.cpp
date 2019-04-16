#include "JFVector3.h"
#include <math.h>

using namespace JFFramework;

const JFVector3 JFFramework::JFVector3::One = JFVector3(1);
const JFVector3 JFFramework::JFVector3::Zero = JFVector3(0);

JFFramework::JFVector3::JFVector3()
	: x(0.0f), y(0.0f), z(0.0f)
{}

JFFramework::JFVector3::JFVector3(float s)
	: x(s), y(s), z(s)
{}

JFFramework::JFVector3::JFVector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{}

JFVector3 JFFramework::JFVector3::operator*(float s) const
{
	return JFVector3(x * s, y * s, z * s);
}

JFVector3 JFFramework::JFVector3::operator/(float s) const
{
	return JFVector3(x / s, y / s, z / s);
}

JFVector3& JFFramework::JFVector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

JFVector3 & JFFramework::JFVector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

JFVector3 JFFramework::JFVector3::operator+(const JFVector3& v) const
{
	return JFVector3(x + v.x, y + v.y, z + v.y);
}

JFVector3 JFFramework::JFVector3::operator-(const JFVector3& v) const
{
	return JFVector3(x - v.x, y - v.y, z - v.y);
}

JFVector3 JFFramework::JFVector3::operator*(const JFVector3& v) const
{
	return JFVector3(x * v.x, y * v.y, z * v.y);
}

JFVector3 JFFramework::JFVector3::operator/(const JFVector3 & v) const
{
	return JFVector3(x / v.x, y / v.y, z / v.y);
}

JFVector3& JFFramework::JFVector3::operator+=(const JFVector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

JFVector3& JFFramework::JFVector3::operator-=(const JFVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

JFVector3& JFFramework::JFVector3::operator*=(const JFVector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

JFVector3& JFFramework::JFVector3::operator/=(const JFVector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

float JFFramework::JFVector3::Dot(const JFVector3& v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

float JFFramework::JFVector3::Dot(const JFVector3 & v1, const JFVector3 & v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

JFVector3 JFFramework::JFVector3::Cross(const JFVector3& v) const
{
	// https://en.wikipedia.org/wiki/Cross_product
	return JFVector3((y * v.z) - (z * v.y),
					 (z * v.x) - (x * v.z),
					 (x * v.y) - (y * v.x));
}

JFVector3 JFFramework::JFVector3::Cross(const JFVector3& v1, const JFVector3& v2)
{
	return JFVector3((v1.y * v2.z) - (v1.z * v2.y),
					 (v1.z * v2.x) - (v1.x * v2.z),
					 (v1.x * v2.y) - (v1.y * v2.x));
}

float JFFramework::JFVector3::Length() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

float JFFramework::JFVector3::LengthSqrt() const
{
	return (x * x) + (y * y) + (z * z);
}

JFVector3& JFFramework::JFVector3::Normalize()
{
	float lengthSqrt = (x * x) + (y * y) + (z * z);
	if (lengthSqrt > 0.0f)
	{
		float lengthInv = 1.0f / sqrtf(lengthSqrt);
		x *= lengthInv;
		y *= lengthInv;
		z *= lengthInv;
	}

	return *this;
}
