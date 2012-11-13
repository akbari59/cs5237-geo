#include "trist.h"
void Trist::setVoronoiVertex(OrTri tri, const LongInt& x, const LongInt& y, const LongInt& denominator)
{
	triangles[tri>>3].setVoronoiVertex(x, y, denominator);
}