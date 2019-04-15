#include "JFVector2.h"

using namespace JFFramework;

JFFramework::JFVector2::JFVector2()
	: x(0)
	, y(0)
{
}

JFFramework::JFVector2::JFVector2(float _x, float _y)
	: x(_x) 
	, y(_y)
{
}

JFVector2 JFFramework::JFVector2::operator+(const JFVector2 & v) const
{
	return JFVector2(x + v.x, y + v.x);
}

JFVector2 JFFramework::JFVector2::operator-(const JFVector2 & v) const
{
	return JFVector2(x - v.x, y - v.y);
}
