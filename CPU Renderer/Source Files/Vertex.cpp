#include "StdAfx.h"
#include "Vertex.h"
#include "Vector3D.h"

// Vector needs to have a position and colour. 
Vertex::Vertex(void)
{
	Initiailise(Vector3D(), 0);
}

Vertex::Vertex(Vector3D mPosition, int mColour)
{
	Initiailise(mPosition, mColour);
}

Vertex::Vertex(const Vertex& rhs)
{
	Copy(rhs);
}

Vertex::~Vertex(void)
{
}

// Getter and setters for vertex position
Vector3D Vertex::GetPosition(void) const
{
	return _Position;
}

void Vertex::SetPosition(Vector3D Position)
{
	_Position = Position;
}


// Getter and setters for colour
int Vertex::GetColour(void) const
{
	return _Colour;
}

void Vertex::SetColour(int Colour)
{
	_Colour = Colour;
}

// Operator overloads
Vertex& Vertex::operator= (const Vertex &rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}



// Initialisation of position and colour for the vertex
void Vertex::Initiailise(Vector3D Position, int Colour)
{
	_Position = Position;
	_Colour = Colour;
}

// Copy constructor
void Vertex::Copy(const Vertex& rhs)
{
	_Position = rhs.GetPosition();
	_Colour = rhs.GetColour();
}
