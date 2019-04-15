#pragma once

#include "../JFInclude.h"

#define PI 3.14159265359

FORCEINLINE float RadianToDegree(float radian)
{
	return radian * (180.0f / static_cast<float>(PI));
}
FORCEINLINE double RadianToDegree(double radian)
{
	return radian * (180.0 / PI);
}

FORCEINLINE float DegreeToRadian(float degree)
{
	return degree * (static_cast<float>(PI) / 180.0f);
}
FORCEINLINE double DegreeToRadian(double degree)
{
	return degree * (PI / 180.0);
}

template<class T, class U>
decltype(auto) Min(const T& a, const U& b)
{
	return (a < b) ? a : b;
}

template<class T, class U, class... V>
decltype(auto) Min(const T& a, const U& b, const V&... args)
{
	return Min(a, Min(b, args...));
}

template<class T, class U>
decltype(auto) Max(const T& a, const U& b)
{
	return (a > b) ? a : b;
}

template<class T, class U, class... V>
decltype(auto) Max(const T& a, const U& b, const V&... args)
{
	return Max(a, Max(b, args...));
}