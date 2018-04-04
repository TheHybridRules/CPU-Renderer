#pragma once
#include "Vector3D.h"

class Vector3D;

class Matrix4X4
{
public:
	//Empty matrix constructor
	Matrix4X4(void);
	//4x4 matrix constructor
	Matrix4X4(
		float, float, float, float,
		float, float, float, float,
		float, float, float, float,
		float, float, float, float);
	//A copy of the constructor
	Matrix4X4(const Matrix4X4& rhs);
	//Matrix destructor
	~Matrix4X4(void);

	//Gets matrix
	float GetA(int, int) const;
	//Sets matrix
	void SetA(int, int, float);

	Matrix4X4& operator= (const Matrix4X4 &rhs);

	//Multiplies 2 matrices and returns a matrix
	Matrix4X4 operator*(const Matrix4X4 &other) const;
	//Multiplies a matrix by a vector and returns vector
	Vector3D operator*(const Vector3D &other) const;
	//Inverses a orthonormal matrix
	Matrix4X4 Inverse(const Matrix4X4 &other) const;

private:

	float _matrix4x4[4][4];
	void Initiailise(
		float a11, float a12, float a13, float a14,
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44);
	void Copy(const Matrix4X4& rhs);
};


