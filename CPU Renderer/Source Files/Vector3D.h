#pragma once
class Vector3D
{
public:
	Vector3D(void);
	Vector3D(float x, float y, float z, float w);
	//Vector3D(const Vector3D &rhs);
	~Vector3D(void);
	
	float GetX(void) const;
	void SetX(float x);

	float GetY(void) const;
	void SetY(float y);

	float GetZ(void) const;
	void SetZ(float z);

	float GetW(void) const;
	void SetW(float w);
	//operators for 3D vectors
	Vector3D operator= (const Vector3D &rhs);
	Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;

	const float DotProduct(const Vector3D &other) const;
	const Vector3D CrossProduct(const Vector3D &other) const;


private:
	float _x;
	float _y;
	float _z;
	float _w;

	void Copy(const Vector3D &rhs);
	void Initiailise(float x, float y, float z, float w);
};


