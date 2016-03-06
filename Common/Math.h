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
	{
		Matrix4f n;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				n.m[i][j] = m[j][i];
			}
		}

		return n;
	}


	inline void InitIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	inline Matrix4f operator*(const Matrix4f& Right) const
	{
		Matrix4f Ret;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				Ret.m[i][j] = m[i][0] * Right.m[0][j] +
					m[i][1] * Right.m[1][j] +
					m[i][2] * Right.m[2][j] +
					m[i][3] * Right.m[3][j];
			}
		}

		return Ret;
	}

	Vector4f operator*(const Vector4f& v) const
	{
		Vector4f r;

		r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
		r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
		r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
		r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

		return r;
	}

	operator const float*() const
	{
		return &(m[0][0]);
	}

	void Print() const
	{
		for (int i = 0; i < 4; i++) {
			printf("%f %f %f %f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
		}
	}

	float Determinant() const;

	Matrix4f& Inverse();

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
	void InitRotateTransform(float RotateX, float RotateY, float RotateZ);
	void InitRotateTransform(const Quaternion& quat);
	void InitTranslationTransform(float x, float y, float z);
	void InitCameraTransform(const Vector3f& Target, const Vector3f& Up);
	void InitPersProjTransform(const PersProjInfo& p);
	void InitOrthoProjTransform(const PersProjInfo& p);
};

struct Quaternion
{
	float x, y, z, w;

	Quaternion(float _x, float _y, float _z, float _w);

	void Normalize();
	Quaternion Conjugate();
	Vector3f ToDegrees();
};

Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const Vector3f& v);

struct PersProjInfo
{
	float FOV;
	float width;
	float height;
	float zNear;
	float zFar;
};

#endif