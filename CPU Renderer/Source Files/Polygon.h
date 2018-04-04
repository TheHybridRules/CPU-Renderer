#pragma once
#include "Vertex.h"

//Class to store the vertex of the 3 tris that make a polygon face. 

class Polygonface
{
public:
	Polygonface(void);
	Polygonface
		(Vertex PointA,
		Vertex PointB,
		Vertex PointC);

	Polygonface(const Polygonface& rhs);
	~Polygonface(void);

	Vertex GetPointA(void) const;
	void SetPointA(Vertex PointA);

	Vertex GetPointB(void) const;
	void SetPointB(Vertex PointB);

	Vertex GetPointC(void) const;
	void SetPointC(Vertex PointC);

	Polygonface& operator= (const Polygonface &rhs);

private:
	Vertex _pointA;
	Vertex _pointB;
	Vertex _pointC;

	void Initiailise(Vertex PointA, Vertex PointB, Vertex PointC);
	void Copy(const Polygonface& rhs);
};

