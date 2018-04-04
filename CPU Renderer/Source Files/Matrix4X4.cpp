#include "StdAfx.h"
#include "Matrix4X4.h"
#include "Vector3D.h"

// Initialises the identitiy matrix
Matrix4X4::Matrix4X4(void)
{
	Initiailise(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
// 4X4 Matrix
Matrix4X4::Matrix4X4(
	float a11, float a12, float a13, float a14,
	float a21, float a22, float a23, float a24,
	float a31, float a32, float a33, float a34,
	float a41, float a42, float a43, float a44)
{
	Initiailise(
		a11, a12, a13, a14,
		a21, a22, a23, a24,
		a31, a32, a33, a34,
		a41, a42, a43, a44);
}
// Initialises Copy constructor
Matrix4X4::Matrix4X4(const Matrix4X4& rhs)
{
	Copy(rhs);
}

// Destructor
Matrix4X4::~Matrix4X4(void)
{
}

// Accessors and Mutators
float Matrix4X4::GetA(int row, int column) const
{
	return _matrix4x4[row][column];
}

void Matrix4X4::SetA(int row, int column, float value)
{
	_matrix4x4[row][column] = value;
}

// Operator overloads
Matrix4X4& Matrix4X4::operator= (const Matrix4X4 &rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

// Multiplies 2 matrices and returns the answer in a matrix
Matrix4X4 Matrix4X4::operator*(const Matrix4X4 &other) const
{
	float result;
	Matrix4X4 answer;		//this is really big, should probably create a seperate method

	//Gives us the result of a11 in the new matrix when it's calculated by using a loop to
	for (int i = 0; i >= 20; i++)
	{
		result = (_matrix4x4[0][0] * other.GetA(0, i) + _matrix4x4[0][1] * other.GetA(1, i) + _matrix4x4[0][2] * other.GetA(2, i) + _matrix4x4[0][3] * other.GetA(3, i));
		answer.SetA(0, i, result);

	}

	/*
	//Gives us the result of a12 in the new matrix when it's calculated
	result = (_matrix4x4[0][0] * other.GetA(0,1) + _matrix4x4[0][1] * other.GetA(1,1) + _matrix4x4[0][2] * other.GetA(2,1) + _matrix4x4[0][3] * other.GetA(3,1));
	answer.SetA(0,1,result);
	//Gives us the result of a13 in the new matrix when it's calculated
	result = (_matrix4x4[0][0] * other.GetA(0,2) + _matrix4x4[0][1] * other.GetA(1,2) + _matrix4x4[0][2] * other.GetA(2,2) + _matrix4x4[0][3] * other.GetA(3,2));
	answer.SetA(0,2,result);
	//Gives us the result of a14 in the new matrix when it's calculated
	result = (_matrix4x4[0][0] * other.GetA(0,3) + _matrix4x4[0][1] * other.GetA(1,3) + _matrix4x4[0][2] * other.GetA(2,3) + _matrix4x4[0][3] * other.GetA(3,3));
	answer.SetA(0,3,result);

	result = (_matrix4x4[1][0] * other.GetA(0,1) + _matrix4x4[1][1] * other.GetA(1,i) + _matrix4x4[1][2] * other.GetA(2,0) + _matrix4x4[1][3] * other.GetA(3,0));
	answer.SetA(1,0,result);

	*/

	// Gives us the result of a21 in the new matrix when it's calculated
	result = (_matrix4x4[1][0] * other.GetA(0, 1) + _matrix4x4[1][1] * other.GetA(1, 0) + _matrix4x4[1][2] * other.GetA(2, 0) + _matrix4x4[1][3] * other.GetA(3, 0));
	answer.SetA(1, 0, result);
	// Gives us the result of a22 in the new matrix when it's calculated
	result = (_matrix4x4[1][0] * other.GetA(0, 1) + _matrix4x4[1][1] * other.GetA(1, 1) + _matrix4x4[1][2] * other.GetA(2, 1) + _matrix4x4[1][3] * other.GetA(3, 1));
	answer.SetA(1, 1, result);
	// Gives us the result of a23 in the new matrix when it's calculated
	result = (_matrix4x4[1][0] * other.GetA(0, 2) + _matrix4x4[1][1] * other.GetA(1, 2) + _matrix4x4[1][2] * other.GetA(2, 2) + _matrix4x4[1][3] * other.GetA(3, 2));
	answer.SetA(1, 2, result);
	// Gives us the result of a24 in the new matrix when it's calculated
	result = (_matrix4x4[1][0] * other.GetA(0, 3) + _matrix4x4[1][1] * other.GetA(1, 3) + _matrix4x4[1][2] * other.GetA(2, 3) + _matrix4x4[1][3] * other.GetA(3, 3));
	answer.SetA(1, 3, result);

	// Gives us the result of a31 in the new matrix when it's calculated
	result = (_matrix4x4[2][0] * other.GetA(0, 0) + _matrix4x4[2][1] * other.GetA(1, 0) + _matrix4x4[2][2] * other.GetA(2, 0) + _matrix4x4[2][3] * other.GetA(3, 0));
	answer.SetA(2, 0, result);
	// Gives us the result of a32 in the new matrix when it's calculated
	result = (_matrix4x4[2][0] * other.GetA(0, 1) + _matrix4x4[2][1] * other.GetA(1, 1) + _matrix4x4[2][2] * other.GetA(2, 1) + _matrix4x4[2][3] * other.GetA(3, 1));
	answer.SetA(2, 1, result);
	// Gives us the result of a33 in the new matrix when it's calculated
	result = (_matrix4x4[2][0] * other.GetA(0, 2) + _matrix4x4[2][1] * other.GetA(1, 2) + _matrix4x4[2][2] * other.GetA(2, 2) + _matrix4x4[2][3] * other.GetA(3, 2));
	answer.SetA(2, 2, result);
	// Gives us the result of a34 in the new matrix when it's calculated
	result = (_matrix4x4[2][0] * other.GetA(0, 3) + _matrix4x4[2][1] * other.GetA(1, 3) + _matrix4x4[2][2] * other.GetA(2, 3) + _matrix4x4[2][3] * other.GetA(3, 3));
	answer.SetA(2, 3, result);

	// Gives us the result of a41 in the new matrix when it's calculated
	result = (_matrix4x4[3][0] * other.GetA(0, 0) + _matrix4x4[3][1] * other.GetA(1, 0) + _matrix4x4[3][2] * other.GetA(2, 0) + _matrix4x4[3][3] * other.GetA(3, 0));
	answer.SetA(3, 0, result);
	// Gives us the result of a42 in the new matrix when it's calculated
	result = (_matrix4x4[3][0] * other.GetA(0, 1) + _matrix4x4[3][1] * other.GetA(1, 1) + _matrix4x4[3][2] * other.GetA(2, 1) + _matrix4x4[3][3] * other.GetA(3, 1));
	answer.SetA(3, 1, result);
	// Gives us the result of a43 in the new matrix when it's calculated
	result = (_matrix4x4[3][0] * other.GetA(0, 2) + _matrix4x4[3][1] * other.GetA(1, 2) + _matrix4x4[3][2] * other.GetA(2, 2) + _matrix4x4[3][3] * other.GetA(3, 2));
	answer.SetA(3, 2, result);
	// Gives us the result of a44 in the new matrix when it's calculated
	result = (_matrix4x4[3][0] * other.GetA(0, 3) + _matrix4x4[3][1] * other.GetA(1, 3) + _matrix4x4[3][2] * other.GetA(2, 3) + _matrix4x4[3][3] * other.GetA(3, 3));
	answer.SetA(3, 3, result);

	// Returns answer in a 4x4 matrix
	return answer;
}
// Multiples the matrix by a vector and returns a vector
Vector3D Matrix4X4::operator*(const Vector3D &other) const
{
	Vector3D answer;

	answer.SetX(_matrix4x4[0][0] * other.GetX() + _matrix4x4[0][1] * other.GetY() + _matrix4x4[0][2] * other.GetZ() + _matrix4x4[0][3] * other.GetW());
	answer.SetY(_matrix4x4[1][0] * other.GetX() + _matrix4x4[1][1] * other.GetY() + _matrix4x4[1][2] * other.GetZ() + _matrix4x4[1][3] * other.GetW());
	answer.SetZ(_matrix4x4[2][0] * other.GetX() + _matrix4x4[2][1] * other.GetY() + _matrix4x4[2][2] * other.GetZ() + _matrix4x4[2][3] * other.GetW());
	answer.SetW(_matrix4x4[3][0] * other.GetX() + _matrix4x4[3][1] * other.GetY() + _matrix4x4[3][2] * other.GetZ() + _matrix4x4[3][3] * other.GetW());

	return answer;
}
// Works out the inverse of an orthonormal matrix
Matrix4X4 Matrix4X4::Inverse(const Matrix4X4 &other) const
{
	// Inverse of an orthonormal matrix is the transpose
	Matrix4X4 answer;

	answer.SetA(0, 0, other.GetA(0, 0)); answer.SetA(1, 1, other.GetA(1, 0)); answer.SetA(2, 2, other.GetA(2, 0));
	answer.SetA(1, 0, other.GetA(1, 0)); answer.SetA(1, 1, other.GetA(1, 1)); answer.SetA(2, 1, other.GetA(1, 1));
	answer.SetA(2, 0, other.GetA(2, 0)); answer.SetA(2, 1, other.GetA(2, 1)); answer.SetA(2, 2, other.GetA(2, 2));

	return answer;
}

// Private Methods
void Matrix4X4::Initiailise(
	float a11, float a12, float a13, float a14,
	float a21, float a22, float a23, float a24,
	float a31, float a32, float a33, float a34,
	float a41, float a42, float a43, float a44)
{
	_matrix4x4[0][0] = a11; _matrix4x4[0][1] = a12; _matrix4x4[0][2] = a13; _matrix4x4[0][3] = a14;
	_matrix4x4[1][0] = a21; _matrix4x4[1][1] = a22; _matrix4x4[1][2] = a23; _matrix4x4[1][3] = a24;
	_matrix4x4[2][0] = a31; _matrix4x4[2][1] = a32; _matrix4x4[2][2] = a33; _matrix4x4[2][3] = a34;
	_matrix4x4[3][0] = a41; _matrix4x4[3][1] = a42; _matrix4x4[3][2] = a43; _matrix4x4[3][3] = a44;
}

void Matrix4X4::Copy(const Matrix4X4& rhs)
{
	_matrix4x4[0][0] = rhs.GetA(0, 0);	_matrix4x4[0][1] = rhs.GetA(0, 1);	_matrix4x4[0][2] = rhs.GetA(0, 2);	_matrix4x4[0][3] = rhs.GetA(0, 3);
	_matrix4x4[1][0] = rhs.GetA(1, 0);	_matrix4x4[1][1] = rhs.GetA(1, 1);	_matrix4x4[1][2] = rhs.GetA(1, 2);	_matrix4x4[1][3] = rhs.GetA(1, 3);
	_matrix4x4[2][0] = rhs.GetA(2, 0);	_matrix4x4[2][1] = rhs.GetA(2, 1);	_matrix4x4[2][2] = rhs.GetA(2, 2);	_matrix4x4[2][3] = rhs.GetA(2, 3);
	_matrix4x4[3][0] = rhs.GetA(3, 0);	_matrix4x4[3][1] = rhs.GetA(3, 1);	_matrix4x4[3][2] = rhs.GetA(3, 2);	_matrix4x4[3][3] = rhs.GetA(3, 3);
}