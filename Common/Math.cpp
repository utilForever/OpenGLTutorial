#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <random>

#include "Math.h"

inline float ToRadian(float x)
{
	return x * M_PI / 180.0f;
}

inline float ToDegree(float x)
{
	return x * 180.0f / M_PI;
}

float RandomFloat()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	return (gen() / RAND_MAX);
}

Vector2f::Vector2f()
	: x(0.0f), y(0.0f)
{
	
}

Vector2f::Vector2f(float _x, float _y)
	: x(_x), y(_y)
{
	
}

Vector3f::Vector3f()
	: x(0.0f), y(0.0f), z(0.0f)
{
	
}

Vector3f::Vector3f(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
	
}

Vector3f::Vector3f(const float* pFloat)
	: x(pFloat[0]), y(pFloat[0]), z(pFloat[0])
{
	
}

Vector3f::Vector3f(float f)
	: x(f), y(f), z(f)
{
	
}

Vector3f& Vector3f::operator+=(const Vector3f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}