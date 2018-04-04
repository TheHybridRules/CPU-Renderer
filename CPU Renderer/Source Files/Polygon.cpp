#include "StdAfx.h"
#include "Polygon.h"


// Constructor
Polygonface::Polygonface(void)
{
}

Polygonface::Polygonface(Vertex PointA,	Vertex PointB,	Vertex PointC)
{
	Initiailise(Vertex(), Vertex(), Vertex());
}
//Copy constructor
Polygonface::Polygonface(const Polygonface& rhs)
{
	Copy(rhs);
}
//Destructor
Polygonface::~Polygonface(void)
{
}

//Acessors and mutators
Vertex Polygonface::GetPointA(void) const
{
	return _pointA;
}
void Polygonface::SetPointA(Vertex PointA)
{
	_pointA = PointA;
}

Vertex Polygonface::GetPointB(void) const
{
	return _pointB;
}
void Polygonface::SetPointB(Vertex PointB)
{
	_pointB = PointB;
}

Vertex Polygonface::GetPointC(void) const
{
	return _pointC;
}
void Polygonface::SetPointC(Vertex PointC)
{
	_pointC = PointC;
}

// Operator overloads
Polygonface& Polygonface::operator= (const Polygonface &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

//private

void Polygonface::Initiailise(Vertex PointA, Vertex PointB, Vertex PointC)
{
	_pointA = PointA;
	_pointB = PointB;
	_pointC = PointC;
}
void Polygonface::Copy(const Polygonface& rhs)
{
	_pointA = rhs.GetPointA();
	_pointB = rhs.GetPointB();
	_pointC = rhs.GetPointC();
}