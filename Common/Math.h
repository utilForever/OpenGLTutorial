#ifndef MATRIX_H
#define MATRIX_H

#include <matrix3x3.h>
#include <matrix4x4.h>

inline float ToRadian(float x);
inline float ToDegree(float x);

float RandomFloat();

struct Vector2i
{
	int x;
	int y;
};

struct Vector2f
{
	float x;
	float y;

	Vector2f();
	Vector2f(float _x, float _y);
};


struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f();
	Vector3f(float _x, float _y, float _z);
	Vector3f(const float* pFloat);
	Vector3f(float f);

	Vector3f& operator+=(const Vector3f& rhs);
	Vector3f& operator-=(const Vector3f& rhs);
	Vector3f& operator*=(float f);

	Vector3f Cross(const Vector3f& v) const;
	Vector3f& Normalize();
	void Rotate(float angle, const Vector3f& axis);
	void Print() const;
};

struct Vector4f
{
	float x;
	float y;
	float z;
	float w;

	Vector4f();
	Vector4f(float _x, float _y, float _z, float _w);

	void Print() const;
	Vector3f To3f() const;
};

inline Vector3f operator+(const Vector3f& lhs, const Vector3f& rhs);
inline Vector3f operator-(const Vector3f& lhs, const Vector3f& rhs);
inline Vector3f operator*(const Vector3f& lhs, float f);
inline Vector4f operator/(const Vector4f& lhs, float f);

struct Quaternion
{
	float x, y, z, w;

	Quaternion(float _x, float _y, float _z, float _w);

	void Normalize();
	Quaternion Conjugate();
	Vector3f ToDegrees();
};

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& q, const Vector3f& v);

struct PerspectiveProjcetionInfo
{
	float FOV;
	float width;
	float height;
	float zNear;
	float zFar;
};

class Matrix4f
{
public:
	float m[4][4];

	Matrix4f();

	// constructor from Assimp matrix
	Matrix4f(const aiMatrix4x4& AssimpMatrix);
	Matrix4f(const aiMatrix3x3& AssimpMatrix);
	Matrix4f(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);

	void SetZero();
	Matrix4f Transpose() const;
	inline void InitIdentity();

	inline Matrix4f operator*(const Matrix4f& rhs) const;
	Vector4f operator*(const Vector4f& v) const;

	void Print() const;
	float Determinant() const;

	Matrix4f& Inverse();

	void InitScaleTransform(float scaleX, float scaleY, float scaleZ);
	void InitRotateTransform(float rotateX, float rotateY, float rotateZ);
	void InitRotateTransform(const Quaternion& quat);
	void InitTranslationTransform(float x, float y, float z);
	void InitCameraTransform(const Vector3f& target, const Vector3f& up);
	void InitPerspectiveProjectionTransform(const PerspectiveProjcetionInfo& p);
	void InitOrthogonalProjectionTransform(const PerspectiveProjcetionInfo& p);
};

#endif