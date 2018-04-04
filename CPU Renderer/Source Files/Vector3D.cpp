#include "stdafx.h"
#include "Vector3D.h"


Vector3D::Vector3D()
{
	Initiailise(0.0f, 0.0f, 0.0f, 1.0f);
}

Vector3D::Vector3D(float x, float y, float z, float w)
{
	Initiailise(x, y, z, w);
}


Vector3D::~Vector3D()
{
}


float Vector3D::GetX(void) const
{
	return _x;
}

void Vector3D::SetX(float x)
{
	_x = x;
}

float Vector3D::GetY(void) const
{
	return _y;
}

void Vector3D::SetY(float y)
{
	_y = y;
}

float Vector3D::GetZ(void) const
{
	return _z;
}

void Vector3D::SetZ(float z)
{
	_z = z;
}

float Vector3D::GetW(void) const
{
	return _w;
}

void Vector3D::SetW(float w)
{
	_w = w;
}


Vector3D Vector3D::operator= (const Vector3D &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}


Vector3D Vector3D::operator+(const Vector3D &other) const
{
	Vector3D result;
	result.SetX(_x + other.GetX());
	result.SetY(_y + other.GetY());
	result.SetZ(_z + other.GetZ());
	result.SetW(1);
	return result;
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
	Vector3D result;
	result.SetX(_x - other.GetX());
	result.SetY(_y - other.GetY());
	result.SetZ(_z - other.GetZ());
	result.SetW(1);
	return result;
}


const float Vector3D::DotProduct(const Vector3D &other) const
{
	float result;
	float answer;

	answer = _x * other.GetX();
	result = +answer;

	answer = _y * other.GetY();
	result = +answer;

	answer = _z * other.GetZ();
	result = +answer;

	result = +1;

	return result;
}
const Vector3D Vector3D::CrossProduct(const Vector3D &other) const
{
	Vector3D result;
	result.SetX((_y * other.GetZ()) - (_z * other.GetY()));
	result.SetY((_z * other.GetX()) - (_x * other.GetZ()));
	result.SetZ((_x * other.GetY()) - (_y * other.GetX()));
	result.SetW(1);

	return result;
}


void Vector3D::Initiailise(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

void Vector3D::Copy(const Vector3D& rhs)
{
	_x = rhs.GetX();
	_y = rhs.GetY();
	_z = rhs.GetZ();
	_w = rhs.GetW();

}