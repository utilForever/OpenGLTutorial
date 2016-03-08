#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <random>
#include <cassert>

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
	const float _x = y * v.z - z * v.y;
	const float _y = z * v.x - x * v.z;
	const float _z = x * v.y - y * v.x;

	return Vector3f(_x, _y, _z);
}

Vector3f& Vector3f::Normalize()
{
	const float length = sqrtf(x * x + y * y + z * z);

	x /= length;
	y /= length;
	z /= length;

	return *this;
}

void Vector3f::Rotate(float angle, const Vector3f& axis)
{
	const float sinHalfAngle = sinf(ToRadian(angle / 2));
	const float cosHalfAngle = cosf(ToRadian(angle / 2));

	const float Rx = axis.x * sinHalfAngle;
	const float Ry = axis.y * sinHalfAngle;
	const float Rz = axis.z * sinHalfAngle;
	const float Rw = cosHalfAngle;

	Quaternion rotationQ(Rx, Ry, Rz, Rw);
	Quaternion conjugateQ = rotationQ.Conjugate();
	Quaternion W = rotationQ * (*this) * conjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
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
	float length = sqrtf(x * x + y * y + z * z + w * w);

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Quaternion Quaternion::Conjugate() const
{
	Quaternion ret(-x, -y, -z, w);

	return ret;
}

Vector3f Quaternion::ToDegrees() const
{
	float f[3];

	f[0] = atan2(x * z + y * w, x * w - y * z);
	f[1] = acos(-x * x - y * y - z * z - w * w);
	f[2] = atan2(x * z - y * w, x * w + y * z);

	f[0] = ToDegree(f[0]);
	f[1] = ToDegree(f[1]);
	f[2] = ToDegree(f[2]);

	return Vector3f(f);
}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
	const float w = (lhs.w * rhs.w) - (lhs.x * rhs.x) - (lhs.y * rhs.y) - (lhs.z * rhs.z);
	const float x = (lhs.x * rhs.w) + (lhs.w * rhs.x) + (lhs.y * rhs.z) - (lhs.z * rhs.y);
	const float y = (lhs.y * rhs.w) + (lhs.w * rhs.y) + (lhs.z * rhs.x) - (lhs.x * rhs.z);
	const float z = (lhs.z * rhs.w) + (lhs.w * rhs.z) + (lhs.x * rhs.y) - (lhs.y * rhs.x);

	Quaternion ret(x, y, z, w);

	return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
	const float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	Quaternion ret(x, y, z, w);

	return ret;
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
	m[0][0] = AssimpMatrix.a1;	m[0][1] = AssimpMatrix.a2;	m[0][2] = AssimpMatrix.a3;	m[0][3] = 0.0f;
	m[1][0] = AssimpMatrix.b1;	m[1][1] = AssimpMatrix.b2;	m[1][2] = AssimpMatrix.b3;	m[1][3] = 0.0f;
	m[2][0] = AssimpMatrix.c1;	m[2][1] = AssimpMatrix.c2;	m[2][2] = AssimpMatrix.c3;	m[2][3] = 0.0f;
	m[3][0] = 0.0f;				m[3][1] = 0.0f;				m[3][2] = 0.0f;				m[3][3] = 1.0f;
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
	return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3]
		+ m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3]
		- m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2]
		+ m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1]
		+ m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1]
		- m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
}

Matrix4f& Matrix4f::Inverse()
{
	// Compute the reciprocal determinant
	float det = Determinant();
	if (det == 0.0f)
	{
		// Matrix not invertible. Setting all elements to nan is not really
		// correct in a mathematical sense but it is easy to debug for the
		// programmer.
		/*const float nan = std::numeric_limits<float>::quiet_NaN();
		*this = Matrix4f(
		nan,nan,nan,nan,
		nan,nan,nan,nan,
		nan,nan,nan,nan,
		nan,nan,nan,nan);*/
		assert(0);
		return *this;
	}

	float invdet = 1.0f / det;

	Matrix4f res;
	res.m[0][0] = invdet  * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
	res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
	res.m[0][2] = invdet  * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
	res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
	res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
	res.m[1][1] = invdet  * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
	res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
	res.m[1][3] = invdet  * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
	res.m[2][0] = invdet  * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[2][2] = invdet  * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
	res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
	res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[3][1] = invdet  * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
	res.m[3][3] = invdet  * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
	*this = res;

	return *this;
}

void Matrix4f::InitScaleTransform(float scaleX, float scaleY, float scaleZ)
{
	m[0][0] = scaleX;	m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = 0.0f;
	m[1][0] = 0.0f;		m[1][1] = scaleY;	m[1][2] = 0.0f;		m[1][3] = 0.0f;
	m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = scaleZ;	m[2][3] = 0.0f;
	m[3][0] = 0.0f;		m[3][1] = 0.0f;		m[3][2] = 0.0f;		m[3][3] = 1.0f;
}

void Matrix4f::InitRotateTransform(float rotateX, float rotateY, float rotateZ)
{
	Matrix4f rx, ry, rz;

	const float x = ToRadian(rotateX);
	const float y = ToRadian(rotateY);
	const float z = ToRadian(rotateZ);

	rx.m[0][0] = 1.0f;		rx.m[0][1] = 0.0f;		rx.m[0][2] = 0.0f;		rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f;		rx.m[1][1] = cosf(x);	rx.m[1][2] = -sinf(x);	rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f;		rx.m[2][1] = sinf(x);	rx.m[2][2] = cosf(x);	rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f;		rx.m[3][1] = 0.0f;		rx.m[3][2] = 0.0f;		rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosf(y);	ry.m[0][1] = 0.0f;		ry.m[0][2] = -sinf(y);	ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f;		ry.m[1][1] = 1.0f;		ry.m[1][2] = 0.0f;		ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinf(y);	ry.m[2][1] = 0.0f;		ry.m[2][2] = cosf(y);	ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f;		ry.m[3][1] = 0.0f;		ry.m[3][2] = 0.0f;		ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosf(z);	rz.m[0][1] = -sinf(z);	rz.m[0][2] = 0.0f;		rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinf(z);	rz.m[1][1] = cosf(z);	rz.m[1][2] = 0.0f;		rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f;		rz.m[2][1] = 0.0f;		rz.m[2][2] = 1.0f;		rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f;		rz.m[3][1] = 0.0f;		rz.m[3][2] = 0.0f;		rz.m[3][3] = 1.0f;

	*this = rz * ry * rx;
}

void Matrix4f::InitRotateTransform(const Quaternion& quat)
{
	float yy2 = 2.0f * quat.y * quat.y;
	float xy2 = 2.0f * quat.x * quat.y;
	float xz2 = 2.0f * quat.x * quat.z;
	float yz2 = 2.0f * quat.y * quat.z;
	float zz2 = 2.0f * quat.z * quat.z;
	float wz2 = 2.0f * quat.w * quat.z;
	float wy2 = 2.0f * quat.w * quat.y;
	float wx2 = 2.0f * quat.w * quat.x;
	float xx2 = 2.0f * quat.x * quat.x;
	m[0][0] = -yy2 - zz2 + 1.0f;
	m[0][1] = xy2 + wz2;
	m[0][2] = xz2 - wy2;
	m[0][3] = 0;
	m[1][0] = xy2 - wz2;
	m[1][1] = -xx2 - zz2 + 1.0f;
	m[1][2] = yz2 + wx2;
	m[1][3] = 0;
	m[2][0] = xz2 + wy2;
	m[2][1] = yz2 - wx2;
	m[2][2] = -xx2 - yy2 + 1.0f;
	m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1.0f;
}

void Matrix4f::InitTranslationTransform(float x, float y, float z)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::InitCameraTransform(const Vector3f & target, const Vector3f & up)
{
	Vector3f N = target;
	N.Normalize();
	Vector3f U = up;
	U.Normalize();
	U = U.Cross(N);
	Vector3f V = N.Cross(U);

	m[0][0] = U.x;	m[0][1] = U.y;	m[0][2] = U.z;   m[0][3] = 0.0f;
	m[1][0] = V.x;	m[1][1] = V.y;	m[1][2] = V.z;   m[1][3] = 0.0f;
	m[2][0] = N.x;	m[2][1] = N.y;	m[2][2] = N.z;   m[2][3] = 0.0f;
	m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;  m[3][3] = 1.0f;
}

void Matrix4f::InitPerspectiveProjectionTransform(const PerspectiveProjcetionInfo & p)
{
	const float ar = p.width / p.height;
	const float zRange = p.zNear - p.zFar;
	const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));

	m[0][0] = 1.0f / (tanHalfFOV * ar);	m[0][1] = 0.0f;					m[0][2] = 0.0f;							m[0][3] = 0.0;
	m[1][0] = 0.0f;						m[1][1] = 1.0f / tanHalfFOV;	m[1][2] = 0.0f;							m[1][3] = 0.0;
	m[2][0] = 0.0f;						m[2][1] = 0.0f;					m[2][2] = (-p.zNear - p.zFar) / zRange;	m[2][3] = 2.0f*p.zFar*p.zNear / zRange;
	m[3][0] = 0.0f;						m[3][1] = 0.0f;					m[3][2] = 1.0f;							m[3][3] = 0.0;
}

void Matrix4f::InitOrthogonalProjectionTransform(const PerspectiveProjcetionInfo & p)
{
	const float zRange = p.zFar - p.zNear;

	m[0][0] = 2.0f / p.width;	m[0][1] = 0.0f;				m[0][2] = 0.0f;				m[0][3] = 0.0;
	m[1][0] = 0.0f;				m[1][1] = 2.0f / p.height;	m[1][2] = 0.0f;				m[1][3] = 0.0;
	m[2][0] = 0.0f;				m[2][1] = 0.0f;				m[2][2] = 2.0f / zRange;	m[2][3] = (-p.zFar - p.zNear) / zRange;
	m[3][0] = 0.0f;				m[3][1] = 0.0f;				m[3][2] = 0.0f;				m[3][3] = 1.0;
}
