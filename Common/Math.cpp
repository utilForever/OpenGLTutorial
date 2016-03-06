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

Vector3f& Vector3f::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

Vector3f Vector3f::Cross(const Vector3f& v) const
{

}

Vector3f& Vector3f::Normalize()
{

}

void Vector3f::Rotate(float angle, const Vector3f& axis)
{

}

void Vector3f::Print() const
{
	std::cout << "(" << x << ", " << y << ", " << z << ")";
}

Vector4f::Vector4f()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{

}

Vector4f::Vector4f(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{

}

void Vector4f::Print() const
{
	std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")";
}

Vector3f Vector4f::To3f() const
{
	Vector3f v(x, y, z);
	return v;
}

inline Vector3f operator+(const Vector3f& lhs, const Vector3f& rhs)
{
	Vector3f ret(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);

	return ret;
}

inline Vector3f operator-(const Vector3f& lhs, const Vector3f& rhs)
{
	Vector3f ret(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);

	return ret;
}

inline Vector3f operator*(const Vector3f& lhs, float f)
{
	Vector3f ret(lhs.x * f, lhs.y * f, lhs.z * f);

	return ret;
}

inline Vector4f operator/(const Vector4f& lhs, float f)
{
	Vector4f ret(lhs.x / f, lhs.y / f, lhs.z / f, lhs.w / f);

	return ret;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{

}

void Quaternion::Normalize()
{

}

Quaternion Quaternion::Conjugate()
{

}

Vector3f Quaternion::ToDegrees()
{

}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{

}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{

}

Matrix4f::Matrix4f()
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			m[i][j] = 0.0f;
		}
	}
}

Matrix4f::Matrix4f(const aiMatrix4x4& AssimpMatrix)
{
	m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = AssimpMatrix.a4;
	m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = AssimpMatrix.b4;
	m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = AssimpMatrix.c4;
	m[3][0] = AssimpMatrix.d1; m[3][1] = AssimpMatrix.d2; m[3][2] = AssimpMatrix.d3; m[3][3] = AssimpMatrix.d4;
}

Matrix4f::Matrix4f(const aiMatrix3x3& AssimpMatrix)
{
	m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = 0.0f;
	m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = 0.0f;
	m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrix4f::Matrix4f(
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
	m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
	m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
	m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
}

void Matrix4f::SetZero()
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			m[i][j] = 0.0f;
		}
	}
}

Matrix4f Matrix4f::Transpose() const
{
	Matrix4f n;

	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			n.m[i][j] = m[j][i];
		}
	}

	return n;
}

inline void Matrix4f::InitIdentity()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

inline Matrix4f Matrix4f::operator*(const Matrix4f& rhs) const
{
	Matrix4f ret;

	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			ret.m[i][j] =
				m[i][0] * rhs.m[0][j] +
				m[i][1] * rhs.m[1][j] +
				m[i][2] * rhs.m[2][j] +
				m[i][3] * rhs.m[3][j];
		}
	}

	return ret;
}

Vector4f Matrix4f::operator*(const Vector4f& v) const
{
	Vector4f ret;

	ret.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	ret.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
	ret.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
	ret.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

	return ret;
}

void Matrix4f::Print() const
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			std::cout << m[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

float Matrix4f::Determinant() const
{
	
}

Matrix4f& Matrix4f::Inverse()
{
	
}

void Matrix4f::InitScaleTransform(float scaleX, float scaleY, float scaleZ)
{
}

void Matrix4f::InitRotateTransform(float rotateX, float rotateY, float rotateZ)
{
}

void Matrix4f::InitRotateTransform(const Quaternion & quat)
{
}

void Matrix4f::InitTranslationTransform(float x, float y, float z)
{
}

void Matrix4f::InitCameraTransform(const Vector3f & target, const Vector3f & up)
{
}

void Matrix4f::InitPerspectiveProjectionTransform(const PerspectiveProjcetionInfo & p)
{
}

void Matrix4f::InitOrthogonalProjectionTransform(const PerspectiveProjcetionInfo & p)
{
}
