#pragma once
#include "Vector3D.h"

class Vertex
{
public:
	Vertex(void);
	Vertex(Vector3D Position, int Colour);
	Vertex(const Vertex& rhs);
	~Vertex(void);

	Vector3D GetPosition(void) const;
	void SetPosition(Vector3D Position);

	int GetColour(void) const;
	void SetColour(int Colour);

	Vertex& operator= (const Vertex &rhs);


private:
	Vector3D _Position;
	int _Colour;

	void Initiailise(Vector3D Position, int Colour);
	void Copy(const Vertex& rhs);

};


